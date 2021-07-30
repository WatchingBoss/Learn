import os, sys, json, xlwt, time
from datetime import datetime, timedelta, timezone
import tinvest
import numpy as np
import pandas as pd
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
        raise FileExistsError

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
        for s in stock_dict.values():
            await streaming.candle.subscribe(s.figi, s.m15.interval)

        async for event in streaming:
            stock = stock_dict[event.payload.figi]
            p = event.payload

            if p.interval == tinvest.CandleResolution.min15:
                timeframe = stock.m15
            elif p.interval == tinvest.CandleResolution.hour:
                timeframe = stock.hour
            elif p.interval == tinvest.CandleResolution.day:
                timeframe = stock.day

            if timeframe.candles.loc[0][0] < p.time:
                timeframe.candles.shift(1)
                timeframe.candles.loc[0] = [p.time, p.o, p.h, p.l, p.c, p.v]

            timeframe.candles.loc[0] = [p.time, p.o, p.h, p.l, p.c, p.v]

            timeframe.last_modify_time = event.time


def get_candles(client, figi, tf: inst.Timeframe):
    now = datetime.now(tz=timezone.utc)
    candle_list = []
    max_list = 200
    for _ in range(10):
        if len(candle_list) >= max_list:
            break
        try:
            candles = client.get_market_candles(
                figi, from_=now - tf.delta, to=now, interval=tf.interval
            ).payload.candles
            now -= tf.delta
            for c in candles:
                candle_list.append([c.time, c.o, c.h, c.l, c.c, c.v])
        except tinvest.exceptions.TooManyRequestsError:
            time.sleep(60)

    if len(candle_list) < 200:
        max_list = len(candle_list)

    tf.candles = pd.DataFrame(
        candle_list, columns=['Time', 'Open', 'High', 'Low', 'Close', 'Volume']
        ).sort_values(by='Time', ascending=False, ignore_index=True)[:max_list]


def fill_candles(client, stock_dict):
    for stock in stock_dict.values():
        get_candles(client, stock.figi, stock.day)
        get_candles(client, stock.figi, stock.hour)
        get_candles(client, stock.figi, stock.m15)


async def print_stock(stock_dict):
    for stock in stock_dict.values():
        print(f"Interval: 15m\n"
              f"{stock.m15.candles.loc[0].to_string()}\n"
              f"Last time modify: {stock.m15.last_modify_time.time()}")
        await stock.ema()
        print(stock.m15.ema.to_string())


# async def calc_ema(stock_dict):
#     while True:
#         for stock in stock_dict.values():
#             await stock.ema()
#         await asyncio.sleep(10)


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

    stock_long = {}
    stock_long_short = {}

    client = tinvest.SyncClient(keys['token_tinkoff_real'])

    p = client.get_market_search_by_ticker('CNK').payload.instruments[0]
    stock = Stock(ticker=p.ticker, figi=p.figi, isin=p.isin, currency=p.currency)
    stock_long_short[stock.figi] = stock
    fill_candles(client, stock_long_short)

    # if not os.path.isfile(path_stocks_usd):
    #     get_market_stocks(client, stock_usd)
    #     stocks_to_file(path_data_dir, path_stocks_usd, stock_usd)
    # else:
    #     stocks_from_file(path_data_dir, path_stocks_usd, stock_usd)
    #
    # for stock in stock_usd.values():
    #     if stock.able_for_short:
    #         stock_able_for_short[stock.figi] = stock

    # task_streaming = asyncio.create_task(test_streaming(keys['token_tinkoff_real'], stock_long_short))
    await asyncio.create_task(print_stock(stock_long_short))
    # asyncio.create_task(update_ema(stock_usd))
    # asyncio.create_task(detect_intersection(stock_usd))

    # await task_streaming


if __name__ == "__main__":
    start_time = time.time()
    asyncio.run(main())
    print(f"Seconds: {time.time() - start_time:.3f}")
