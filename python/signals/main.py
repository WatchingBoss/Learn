import os, sys, json, time
from datetime import datetime, timedelta, timezone
import asyncio
import concurrent.futures

import tinvest
import numpy as np
import pandas as pd
from tradingview_ta import TA_Handler, Interval, Exchange

import support
from instrument import Stock, Timeframe


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


def get_candles(client, figi, tf: Timeframe):
    today = datetime.today()
    start = datetime(today.year, today.month, today.day, hour=13, minute=30, tzinfo=timezone.utc)
    candle_list = []
    max_list = 101
    for _ in range(10):
        if len(candle_list) >= max_list:
            break
        try:
            candles = client.get_market_candles(
                figi, from_=start, to=start + timedelta(hours=6, minutes=30), interval=tf.interval
            ).payload.candles
            start -= timedelta(days=1)
            for c in candles:
                candle_list.append([c.time, c.o, c.h, c.l, c.c, c.v])
        except tinvest.exceptions.TooManyRequestsError:
            time.sleep(60)

    if len(candle_list) < max_list:
        max_list = len(candle_list)

    tf.candles = pd.DataFrame(
        candle_list, columns=['Time', 'Open', 'High', 'Low', 'Close', 'Volume']
        ).sort_values(by='Time', ascending=True, ignore_index=True)


def fill_candles(client, stock_dict):
    for stock in stock_dict.values():
        for tf in [stock.m1, stock.m5, stock.m15]:
            get_candles(client, stock.figi, tf)


async def print_stock(stock_dict):
    for stock in stock_dict.values():
        for tf in [stock.m1, stock.m5, stock.m15]:
            tf.ema('ema_10', 10)
            tf.ema('ema_20', 20)
            tf.ema('ema_50', 50)
            tf.macd()
            tf.rsi()
            print(f"Ticker: {stock.ticker}\n"
                  f"Interval: {tf.interval}\n"
                  f"{tf.candles.to_string()}\n"
                  f"Last time modify: {tf.last_modify_time.time()}")


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

    scanning_stocks = {}

    client = tinvest.SyncClient(keys['token_tinkoff_real'])

    stocks = client.get_market_search_by_ticker('CCL').payload.instruments
    for s in stocks:
        scanning_stocks[s.figi] = Stock(s.ticker, s.figi, s.isin, s.currency)

    fill_candles(client, scanning_stocks)
    await print_stock(scanning_stocks)


if __name__ == "__main__":
    start_time = time.time()
    asyncio.run(main())
    print(f"\n\nSeconds: {time.time() - start_time:.3f}")
