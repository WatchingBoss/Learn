import os, sys, json, xlwt, time
from datetime import datetime, timedelta
import tinvest
import numpy as np
import concurrent.futures
import asyncio
import scraper

STOCKS_USD = []
TRADE_STOCKS_USD = []

PATH = {
    'data_dir': os.path.join(os.curdir, 'data'),
    'stocks_usd': os.path.join(os.curdir, 'data', 'stocks_usd' + '.json'),
    'trade_stocks_usd': os.path.join(os.curdir, 'data', 'trade_stocks_usd' + '.json')
}


def get_all_keys(keys):
    with open(os.path.join(os.path.expanduser('~'), 'no_commit', 'info.json')) as f:
        data = json.load(f)
        ttr = data['token_tinkoff_real']
        ttd = data['token_tinkoff_demo']
        keys['token_tinkoff_real'] = ttr
        keys['token_tinkoff_demo'] = ttd


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


def stocks_to_file(file_name, this_list):
    if not os.path.isdir(PATH['data_dir']):
        os.mkdir(PATH['data_dir'])

    output = [stock.output_data(1) for stock in this_list]

    with open(PATH[file_name], 'w') as f:
        json.dump(output, f)


def stocks_from_file(file_name, this_list):
    if not os.path.isdir(PATH['data_dir']):
        print(f"No current directory: {PATH['data_dir']}")
        return 0

    with open(PATH[file_name], 'r') as f:
        input_data = json.load(f)

    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = [executor.submit(Stock, s['ticker'], s['figi'], s['isin'], s['currency']) for s in input_data]
        for future in futures:
            this_list.append(future.result())


def get_market_stocks(client):
    payload = client.get_market_stocks().payload
    stocks_usd = [stock for stock in payload.instruments[:] if stock.currency == 'USD']
    # stocks_rub = [stock for stock in payload.instruments[:] if stock.currency == 'RUB']

    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = [executor.submit(Stock, s.ticker, s.figi, s.isin, s.currency) for s in stocks_usd]
        for future in futures:
            STOCKS_USD.append(future.result())

    STOCKS_USD.sort()


def choose_trade_stocks_usd(client):
    max_high_price = 350
    min_month_high_low_difference = 0.05

    now = datetime.now()
    start_month = now - timedelta(30 * 5)
    start_hour = now - timedelta(7)

    for i in range(len(STOCKS_USD)):
        stock = STOCKS_USD[i]
        try:
            candles_month = client.get_market_candles(
                figi=stock.figi,
                from_=start_month,
                to=now,
                interval=tinvest.CandleResolution.month
            ).payload.candles

            # candles_hour = client.get_market_candles(
            #     figi=stock.figi,
            #     from_=start_hour,
            #     to=now,
            #     interval=tinvest.CandleResolution.hour
            # ).payload.candles
        except tinvest.exceptions.TooManyRequestsError:
            print("Waiting for 61 seconds")
            time.sleep(61)
            i -= 1
            continue
        except tinvest.exceptions.UnexpectedError:
            continue
        print(i)

        try:
            if sorted([candle.h for candle in candles_month])[-1] > max_high_price:
                continue
        except IndexError:
            print([candle.h for candle in candles_month])

        try:
            if np.mean([candle.l / (candle.h - candle.l) for candle in candles_month]) < min_month_high_low_difference:
                continue
        except ZeroDivisionError:
            continue

        TRADE_STOCKS_USD.append(stock)

    TRADE_STOCKS_USD.sort()


def main():
    keys = {
        "token_tinkoff_real": "",
        "token_tinkoff_demo": ""
    }
    get_all_keys(keys)
    client = tinvest.SyncClient(keys['token_tinkoff_real'])

    if not os.path.isfile(PATH['stocks_usd']):
        get_market_stocks(client)
        stocks_to_file('stocks_usd', STOCKS_USD)
    else:
        stocks_from_file('stocks_usd', STOCKS_USD)

    if not os.path.isfile(PATH['trade_stocks_usd']):
        choose_trade_stocks_usd(client)
        stocks_to_file('trade_stocks_usd', TRADE_STOCKS_USD)
    else:
        stocks_from_file('trade_stocks_usd', TRADE_STOCKS_USD)

    print(len(TRADE_STOCKS_USD))
    for stock in TRADE_STOCKS_USD:
        print(stock.ticker)


if __name__ == "__main__":
    main()
