import os, sys, json, xlwt, time
from datetime import datetime, timedelta, timezone
import tinvest
import numpy as np
import concurrent.futures
import asyncio
import support, instrument as inst
from instrument import Stock


def stocks_to_file(folder, file, stocks_dict):
    if not os.path.isdir(folder):
        os.mkdir(folder)

    output = [s.output_data(1) for s in stocks_dict.values()]

    with open(file, 'w') as f:
        json.dump(output, f)


def stocks_from_file(folder, file, stocks_dict):
    if not os.path.isdir(folder):
        print(f"No current directory: {folder}")
        return 0

    with open(file, 'r') as f:
        input_data = json.load(f)

    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = [executor.submit(Stock, s['ticker'], s['figi'], s['isin'], s['currency']) for s in input_data]
        for future in futures:
            stock = future.result()
            stocks_dict[stock.figi] = stock
            stock.check_if_able_for_short()


def get_market_stocks(client, stocks_dict):
    payload = client.get_market_stocks().payload
    stocks_usd = [stock for stock in payload.instruments[:] if stock.currency == 'USD']

    max_high_price = 250
    min_avg_month_high_low_diff = 0.12
    min_avg_day_high_low_diff = 0.025
    min_avg_volume = 100_000

    now = datetime.now()
    start_month = now - timedelta(30 * 3)
    start_day = now - timedelta(20)

    for i in range(len(stocks_usd)):
        stock = stocks_usd[i]
        try:
            candles_month = client.get_market_candles(
                figi=stock.figi, from_=start_month, to=now, interval=tinvest.CandleResolution.month
            ).payload.candles

            candles_day = client.get_market_candles(
                figi=stock.figi, from_=start_day, to=now, interval=tinvest.CandleResolution.day
            ).payload.candles

        except tinvest.exceptions.TooManyRequestsError:
            print("Waiting for 61 seconds")
            time.sleep(61)

            candles_month = client.get_market_candles(
                figi=stock.figi, from_=start_month, to=now, interval=tinvest.CandleResolution.month
            ).payload.candles

            candles_day = client.get_market_candles(
                figi=stock.figi, from_=start_day, to=now, interval=tinvest.CandleResolution.day
            ).payload.candles

        except tinvest.exceptions.UnexpectedError:
            continue

        print(f"{i}: {stock.ticker}")

        if len(candles_month) < 2 or len(candles_day) < 2:
            continue

        try:
            this_max_high = sorted([candle.h for candle in candles_month])[-1]
            print(f"Max high: {this_max_high}")
            if this_max_high > max_high_price:
                continue
        except IndexError:
            print([candle.h for candle in candles_month])

        try:
            difference = np.mean([(candle.h - candle.l) / candle.l for candle in candles_month])
            print(f"Average month high - low difference: {difference:.1%}")
            if difference < min_avg_month_high_low_diff:
                continue
        except ZeroDivisionError:
            continue

        try:
            difference = np.mean([(candle.h - candle.l) / candle.l for candle in candles_day])
            print(f"Average day high - low difference: {difference:.1%}")
            if difference < min_avg_day_high_low_diff:
                continue
        except ZeroDivisionError:
            continue

        try:
            avg_volume = np.mean([candle.v for candle in candles_day])
            print(f"Average 10 days volume: {avg_volume:.1f}")
            if avg_volume < min_avg_volume:
                continue
        except ZeroDivisionError:
            continue

        stocks_dict[stock.figi] = Stock(stock.ticker, stock.figi, stock.isin, stock.currency)


async def test_streaming(key, stock_dict):
    async with tinvest.Streaming(key) as streaming:
        for s in [stock_dict['BBG00MVWLLM2'], stock_dict['BBG000M65M61'], stock_dict['BBG005P7Q881']]:
            await streaming.candle.subscribe(s.figi, tinvest.CandleResolution.min15)
            await streaming.candle.subscribe(s.figi, tinvest.CandleResolution.hour)
            await streaming.candle.subscribe(s.figi, tinvest.CandleResolution.day)

        async for event in streaming:
            stock = stock_dict[event.payload.figi]
            p = event.payload

            if p.interval == tinvest.CandleResolution.min15:
                timeframe = stock.m15
            elif p.interval == tinvest.CandleResolution.hour:
                timeframe = stock.hour
            elif p.interval == tinvest.CandleResolution.day:
                timeframe = stock.day

            if timeframe.candles[-1].t < p.time:
                timeframe.candles.append(inst.Candle(o=p.o, l=p.l, h=p.h, c=p.c, v=p.v, t=p.time))

            c = timeframe.candles[-1]
            c.o = p.o
            c.l = p.l
            c.h = p.h
            c.c = p.c
            c.v = p.v

            timeframe.last_modify_time = event.time


async def get_ema(candles, periods) -> float:
    all_c = [float(candle.c) for candle in candles]

    if len(all_c) >= periods * 2:
        sma_c = all_c[-(periods * 2):-periods]
    elif len(all_c) > periods:
        sma_c = all_c[:-periods]
    else:
        return -1

    sma = float(sum(sma_c) / len(sma_c))
    multiplier = 2 / (periods + 1)

    ema = 0
    for i in range(-periods, -1, 1):
        if i == -periods:
            ema = (all_c[i] - sma) * multiplier + sma
        ema = (all_c[i] - ema) * multiplier + ema

    return ema


async def compute_ema(timeframe: inst.Timeframe):
    task_ema_200 = asyncio.create_task(get_ema(timeframe.candles, 200))
    task_ema_50 = asyncio.create_task(get_ema(timeframe.candles, 50))
    task_ema_20 = asyncio.create_task(get_ema(timeframe.candles, 20))
    task_ema_10 = asyncio.create_task(get_ema(timeframe.candles, 10))
    timeframe.ema_10 = await task_ema_10
    timeframe.ema_20 = await task_ema_20
    timeframe.ema_50 = await task_ema_50
    timeframe.ema_200 = await task_ema_200


async def update_ema(stock_dict):
    while True:
        for stock in [stock_dict['BBG00MVWLLM2'], stock_dict['BBG000M65M61'], stock_dict['BBG005P7Q881']]:
            for timeframe in [stock.m15, stock.hour, stock.day]:
                timeframe.ema_10 = (float(timeframe.candles[-1].c) - timeframe.ema_10) * (2 / (10 + 1)) + timeframe.ema_10
                timeframe.ema_20 = (float(timeframe.candles[-1].c) - timeframe.ema_20) * (2 / (20 + 1)) + timeframe.ema_20
                timeframe.ema_50 = (float(timeframe.candles[-1].c) - timeframe.ema_50) * (2 / (50 + 1)) + timeframe.ema_50
                timeframe.ema_200 = (float(timeframe.candles[-1].c) - timeframe.ema_200) * (2 / (200 + 1)) + timeframe.ema_200
                await asyncio.sleep(10)


async def get_candles(client, figi, timeframe: inst.Timeframe):
    candles = []
    end_period = datetime.now(tz=timezone.utc)

    for _ in range(5):
        try:
            candles += client.get_market_candles(
                figi, from_=end_period - timeframe.delta, to=end_period, interval=timeframe.interval
            ).payload.candles[::-1]
            end_period -= timeframe.delta
        except tinvest.exceptions.TooManyRequestsError:
            await asyncio.sleep(61)

    timeframe.candles.clear()
    timeframe.candles = [
        inst.Candle(o=candle.o, l=candle.o, h=candle.h, c=candle.c, v=candle.v, t=candle.time)
        for candle in candles[::-1]
    ]


async def fill_candles(client, stock_dict):
    for stock in [stock_dict['BBG00MVWLLM2'], stock_dict['BBG000M65M61'], stock_dict['BBG005P7Q881']]:
        await asyncio.gather(
            get_candles(client, stock.figi, stock.day),
            get_candles(client, stock.figi, stock.hour),
            get_candles(client, stock.figi, stock.m15)
        )

        await asyncio.gather(
            compute_ema(stock.day),
            compute_ema(stock.hour),
            compute_ema(stock.m15)
        )


def send_event(ticker: str, interval, msg: str):
    print(f"Ticker: {ticker}\n"
          f"Interval: {interval}\n"
          f"{msg}")


async def detect_intersection_in_timeframe(stock: Stock, tf: inst.Timeframe):
    if tf.ema10_above_20:
        if tf.ema_10 < tf.ema_20:
            tf.ema10_above_20 = False
            send_event(stock.ticker, tf.interval, "EMA 10 under EMA 20")
    else:
        if tf.ema_10 > tf.ema_20:
            tf.ema10_above_20 = True
            send_event(stock.ticker, tf.interval, "EMA 10 above EMA 20")

    if tf.ema50_above_200:
        if tf.ema_50 < tf.ema_200:
            tf.ema50_above_200 = False
            send_event(stock.ticker, tf.interval, "EMA 50 under EMA 200")
    else:
        if tf.ema_50 > tf.ema_200:
            tf.ema50_above_200 = True
            send_event(stock.ticker, tf.interval, "EMA 50 above EMA 200")


async def detect_intersection(stock_dict):
    while True:
        for stock in [stock_dict['BBG00MVWLLM2'], stock_dict['BBG000M65M61'], stock_dict['BBG005P7Q881']]:
            asyncio.create_task(detect_intersection_in_timeframe(stock, stock.m15))
            asyncio.create_task(detect_intersection_in_timeframe(stock, stock.hour))
            asyncio.create_task(detect_intersection_in_timeframe(stock, stock.day))


async def main():
    keys = {
        'token_tinkoff_real': '',
        'token_tinkoff_demo': ''
    }
    support.get_all_keys(keys)

    path_data_dir = os.path.join(os.curdir, 'data')
    path_stocks_usd = os.path.join(path_data_dir, 'stocks_usd' + '.json')

    if not os.path.isdir(path_data_dir):
        os.mkdir(path_data_dir)

    stocks_usd = {}
    stocks_able_for_short = {}

    client = tinvest.SyncClient(keys['token_tinkoff_real'])

    if not os.path.isfile(path_stocks_usd):
        get_market_stocks(client, stocks_usd)
        stocks_to_file(path_data_dir, path_stocks_usd, stocks_usd)
    else:
        stocks_from_file(path_data_dir, path_stocks_usd, stocks_usd)

    for stock in stocks_usd.values():
        if stock.able_for_short:
            stocks_able_for_short[stock.figi] = stock

    # for s in stocks_usd.values():
    #     print(f"{s.ticker}, {s.figi}\n")
    # print(f"There are {len(stocks_usd.values())} stocks to trade")

    # task_fill_candles = asyncio.create_task(fill_candles(client, stocks_usd))
    # await task_fill_candles
    #
    # asyncio.create_task(test_streaming(keys['token_tinkoff_real'], stocks_usd))
    # asyncio.create_task(update_ema(stocks_usd))
    # asyncio.create_task(detect_intersection(stocks_usd))


if __name__ == "__main__":
    start_time = time.time()
    asyncio.run(main())
    print(f"Seconds: {time.time() - start_time:.3f}")
