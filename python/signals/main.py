import os, sys, json, xlwt, time
from datetime import datetime, timedelta, timezone
import tinvest
import numpy as np
import concurrent.futures
import asyncio
import scraper


FIGI_TICKER = {}


def get_all_keys(keys):
    with open(os.path.join(os.path.expanduser('~'), 'no_commit', 'info.json')) as f:
        data = json.load(f)
        keys['token_tinkoff_real'] = data['token_tinkoff_real']
        keys['token_tinkoff_demo'] = data['token_tinkoff_demo']


def show_get_portfolio(client):
    p = client.get_portfolio()
    print(f"My Portfolio:\n"
          f"Tracking id: {p.tracking_id}\n"
          f"Status: {p.status}\n"
          f"Payload:\n")
    for pos in p.payload.positions:
        print(f"Name: {pos.name}\n"
              f"Figi: {pos.figi}\n"
              f"Ticker: {pos.ticker}\n"
              f"Isin: {pos.isin}\n"
              f"Type: {pos.instrument_type}\n"
              f"Balance: {pos.balance}\n"
              f"Blocked: {pos.blocked}\n"
              f"Lots: {pos.lots}\n"
              f"Position price: {pos.average_position_price.value} {pos.average_position_price.currency}\n"
              f"Expected yield: {pos.expected_yield.value} {pos.expected_yield.currency}\n")


def show_get_portfolio_currencies(client):
    p = client.get_portfolio_currencies()
    print(f"My Portfolio currencies:\n"
          f"Tracking id: {p.tracking_id}\n"
          f"Status: {p.status}\n"
          f"Payload:\n")
    for c in p.payload.currencies:
        if not c.blocked:
            continue
        cur = c.currency
        av = c.balance - c.blocked
        print(f"Balance: {c.balance} {cur}\n"
              f"Blocked: {c.blocked} {cur}\n"
              f"Available: {av} {cur}, ~{av / c.balance * 100:.1f}%\n")


def show_get_orders(client):
    print("Orders:\n")
    for order in client.get_orders().payload:
        print(f"OrderID: {order.order_id}\n"
              f"Figi: {order.figi}\n"
              f"Operation: {order.operation}\n"
              f"Status: {order.status}\n"
              f"Requested lots: {order.requested_lots}\n"
              f"Executed lots: {order.executed_lots}\n"
              f"Type: {order.type_}\n"
              f"Price: {order.price}\n")


class Instrument:
    """
    Exchange instrument imlementation
    """
    def __init__(self, ticker, figi, isin, currency):
        self.ticker = ticker
        self.figi = figi
        self.isin = isin
        self.currency = currency


class Stock(Instrument):
    """
    Stock implementation
    """
    def __init__(self, ticker, figi, isin, currency):
        super().__init__(ticker, figi, isin, currency)
        self.data = {}

    def __lt__(self, another):
        return self.ticker < another.ticker

    def add_scraping_data(self):
        if self.currency == 'USD':
            self.data = scraper.check_finviz(self.ticker)

    def output_data(self, level):
        if level == 2:
            return {
                'ticker': self.ticker,
                'figi': self.figi,
                'isin': self.isin,
                'currency': self.currency,
                'name': self.data['name'],
                'sector': self.data['sector'],
                'industry': self.data['industry'],
                'p_e': self.data['p_e'],
                'p_s': self.data['p_s'],
                'p_b': self.data['p_b'],
                'debt_eq': self.data['debt_eq'],
                'short_float': self.data['short_float']
            }
        elif level == 1:
            return {
                'ticker': self.ticker,
                'figi': self.figi,
                'isin': self.isin,
                'currency': self.currency
            }


def stocks_to_file(folder, file, stocks):
    if not os.path.isdir(folder):
        os.mkdir(folder)

    output = [s.output_data(1) for s in stocks]

    with open(file, 'w') as f:
        json.dump(output, f)


def stocks_from_file(folder, file, stocks):
    if not os.path.isdir(folder):
        print(f"No current directory: {folder}")
        return 0

    with open(file, 'r') as f:
        input_data = json.load(f)

    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = [executor.submit(Stock, s['ticker'], s['figi'], s['isin'], s['currency']) for s in input_data]
        for future in futures:
            stocks.append(future.result())

    stocks.sort()


def get_market_stocks(client, stocks_list):
    payload = client.get_market_stocks().payload
    stocks_usd = [stock for stock in payload.instruments[:] if stock.currency == 'USD']

    max_high_price = 200
    min_avg_month_high_low_diff = 0.15
    min_avg_volume = 100_000

    now = datetime.now()
    start_month = now - timedelta(30 * 5)
    start_day = now - timedelta(10)

    for i in range(len(stocks_usd)):
        stock = stocks_usd[i]
        try:
            candles_month = client.get_market_candles(
                figi=stock.figi,
                from_=start_month,
                to=now,
                interval=tinvest.CandleResolution.month
            ).payload.candles

            candles_day = client.get_market_candles(
                figi=stock.figi,
                from_=start_day,
                to=now,
                interval=tinvest.CandleResolution.day
            ).payload.candles

        except tinvest.exceptions.TooManyRequestsError:
            print("Waiting for 61 seconds")
            time.sleep(61)
            i -= 1
            continue
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
            print(f"Average high - low difference: {difference:.1%}")
            if difference < min_avg_month_high_low_diff:
                continue
        except ZeroDivisionError:
            continue

        try:
            avg_volume = np.mean([candle.v for candle in candles_day])
            print(f"Average 10 days volume: {avg_volume}")
            if avg_volume < min_avg_volume:
                continue
        except ZeroDivisionError:
            pass

        stocks_list.append(Stock(stock.ticker, stock.figi, stock.isin, stock.currency))

    stocks_list.sort()


async def test_streaming(key, stocks):
    async with tinvest.Streaming(key) as streaming:
        # for s in stocks:
        #     await streaming.candle.subscribe(s.figi, tinvest.CandleResolution.min5)
        #     await streaming.candle.subscribe(s.figi, tinvest.CandleResolution.min15)
        #     await streaming.candle.subscribe(s.figi, tinvest.CandleResolution.hour)
        await streaming.candle.subscribe(stocks[104].figi, tinvest.CandleResolution.min5)
        await streaming.candle.subscribe(stocks[104].figi, tinvest.CandleResolution.min15)
        await streaming.candle.subscribe(stocks[104].figi, tinvest.CandleResolution.hour)

        async for event in streaming:
            if event.payload.interval == tinvest.CandleResolution.min5:
                m5 = event.payload.time
                print(f"Ticker: {FIGI_TICKER[event.payload.figi]}\n"
                      f"Interval: {event.payload.interval}\n"
                      f"o: {event.payload.o}  l: {event.payload.l}  h: {event.payload.h}  c: {event.payload.c}\n"
                      f"v: {event.payload.v}")
            if event.payload.interval == tinvest.CandleResolution.min15:
                pass
            if event.payload.interval == tinvest.CandleResolution.hour:
                pass


async def fill_candles(client, stocks):
    pass


async def main():
    keys = {
        "token_tinkoff_real": "",
        "token_tinkoff_demo": ""
    }

    path_data_dir = os.path.join(os.curdir, 'data')
    path_stocks_usd = os.path.join(path_data_dir, 'stocks_usd' + '.json')

    stocks_usd = []

    get_all_keys(keys)
    client = tinvest.SyncClient(keys['token_tinkoff_real'])

    if not os.path.isdir(path_data_dir):
        os.mkdir(path_data_dir)

    if not os.path.isfile(path_stocks_usd):
        get_market_stocks(client, stocks_usd)
        stocks_to_file(path_data_dir, path_stocks_usd, stocks_usd)
    else:
        stocks_from_file(path_data_dir, path_stocks_usd, stocks_usd)

    for s in stocks_usd:
        FIGI_TICKER[s.figi] = s.ticker

    await test_streaming(keys['token_tinkoff_real'], stocks_usd)


if __name__ == "__main__":
    asyncio.run(main())
