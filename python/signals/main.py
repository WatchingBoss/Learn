import os, sys, json, time
from datetime import datetime, timedelta, timezone
import asyncio
import concurrent.futures

import tinvest
import numpy as np
import pandas as pd
from tradingview_ta import TA_Handler, Interval, Exchange

import support, instrument as inst
from instrument import Stock


def stocks_to_file(folder, file, stocks_dict):
    if not os.path.isdir(folder):
        os.mkdir(folder)

    output = [s.output_data() for s in stocks_dict.values()]

    with open(file, 'w') as f:
        json.dump(output, f)


def stocks_from_file(folder, file, stocks_dict):
    if not os.path.isdir(folder):
        raise FileExistsError

    with open(file, 'r') as f:
        input_data = json.load(f)

    for s in input_data:
        stock = Stock(s['ticker'], s['figi'], s['isin'], s['currency'])
        stock.data = s['data']
        stocks_dict[stock.figi] = stock

    # with concurrent.futures.ThreadPoolExecutor() as executor:
    #     futures = [executor.submit(Stock, s['ticker'], s['figi'], s['isin'], s['currency']) for s in input_data]
    #     for future in futures:
    #         stock = future.result()
    #         stocks_dict[stock.figi] = stock
    #         stock.check_if_able_for_short()


def get_market_stocks(client, stocks_dict):
    payload = client.get_market_stocks().payload
    stocks_usd = [stock for stock in payload.instruments[:] if stock.currency == 'USD']

    for i in range(len(stocks_usd)):
        stock = stocks_usd[i]
        stocks_dict[stock.figi] = Stock(stock.ticker, stock.figi, stock.isin, stock.currency)


def load_stocks(file, client, stocks_dict):
    with open(file, 'r') as f:
        tickers = f.readline().split(' ')
    for t in tickers:
        stock = client.get_market_search_by_ticker(t).payload.instruments[0]
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
    max_list = 250
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

    if len(candle_list) < 250:
        max_list = len(candle_list)

    tf.candles = pd.DataFrame(
        candle_list, columns=['Time', 'Open', 'High', 'Low', 'Close', 'Volume']
        ).sort_values(by='Time', ascending=True, ignore_index=True)


def fill_candles(client, stock_dict):
    for stock in stock_dict.values():
        # get_candles(client, stock.figi, stock.day)
        # get_candles(client, stock.figi, stock.hour)
        get_candles(client, stock.figi, stock.m15)


async def print_stock(stock_dict):
    for stock in stock_dict.values():
        tf = stock.m15
        print(f"Ticker: {stock.ticker}\n"
              f"Interval: {tf.interval}\n"
              f"{tf.candles}\n"
              f"Last time modify: {tf.last_modify_time.time()}")
        tf.ema()
        print(tf.candles)
        # print(stock.m15.ema.to_string())


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

    all_stocks = {}
    stock_long_only = {}
    stock_long_short = {}

    client = tinvest.SyncClient(keys['token_tinkoff_real'])

    # get_market_stocks(client, all_stocks)
    if os.path.isfile(path_stocks_usd):
        stocks_from_file(path_data_dir, path_stocks_usd, all_stocks)
    if len(all_stocks) < 3:
        load_stocks(os.path.join(path_data_dir, 'stocks' + '.txt'), client, all_stocks)
        with concurrent.futures.ThreadPoolExecutor(max_workers=10) as executor:
            for stock in all_stocks.values():
                executor.submit(stock.add_scraping_data())
        stocks_to_file(path_data_dir, path_stocks_usd, all_stocks)
    # stocks = [s for s in all_stocks.values()]
    # now_stocks = stocks[120:150]

    with concurrent.futures.ThreadPoolExecutor(max_workers=10) as executor:
        for stock in all_stocks.values():
            executor.submit(stock.get_tradingview_data([stock.tv_m5]))

    for s in all_stocks.values():
        print('\n' + s.ticker)
        for tf in [s.tv_m5]:
            print(tf.interval)
            print(tf.sum)
            print(tf.ema)
            print(tf.osc)

    # for stock in stock_long_short.values():
    #     this_stock = TA_Handler(
    #         symbol=stock.ticker,
    #         screener="america",
    #         exchange=stock.data['exchange'],
    #         interval=Interval.INTERVAL_1_DAY
    #     )

    # brent = TA_Handler(
    #     symbol='UKOIL',
    #     screener="cfd",
    #     exchange='FX',
    #     interval=Interval.INTERVAL_15_MINUTES
    # )


if __name__ == "__main__":
    start_time = time.time()
    asyncio.run(main())
    print(f"\n\nSeconds: {time.time() - start_time:.3f}")
