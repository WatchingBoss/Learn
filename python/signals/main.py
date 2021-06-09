import os, datetime, sys, json, xlwt
import tinvest
import concurrent.futures
import scraper

STOCKS_USD = []
STOCKS_RUB = []


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
    _all_instruments_ = 0

    def __init__(self, ticker, figi, isin, currency):
        Instrument._all_instruments_ += 1
        self.ticker = ticker
        self.figi = figi
        self.isin = isin
        self.currency = currency


class Stock(Instrument):
    """
    Stock implementation
    """
    _all_stocks_ = 0

    def __init__(self, ticker, figi, isin, currency):
        super().__init__(ticker, figi, isin, currency)
        data = self.add_scraping_data()
        self.scrap_data = True

        try:
            self.name = data['name']
            self.sector = data['sector']
            self.industry = data['industry']
            self.index = data['index']
            self.capitalization = data['capitalization']
            self.p_e = data['p_e']
            self.p_s = data['p_s']
            self.p_b = data['p_b']
            self.debt_eq = data['debt_eq']
            self.short_float = data['short_float']
            self.target_price = data['target_price']
        except TypeError:
            self.scrap_data = False
            print(f"{self.ticker}: no scaraping data")

        if self.scrap_data:
            Stock._all_stocks_ += 1
            print(Stock._all_stocks_)

    def __lt__(self, another):
        return self.ticker < another.ticker

    def add_scraping_data(self):
        data = {}

        if self.currency == 'USD':
            data = scraper.check_finviz(self.ticker)
        elif self.currency == 'RUB':
            pass
        elif self.currency == 'EUR':
            pass
        else:
            pass

        return data

    def output_data(self):
        return {
            'ticker': self.ticker,
            'figi': self.figi,
            'isin': self.isin,
            'currency': self.currency,
            'name': self.name,
            'sector': self.sector,
            'industry': self.industry,
            'index': self.index,
            'capitalization': self.capitalization,
            'p_e': self.p_e,
            'p_s': self.p_s,
            'p_b': self.p_b,
            'debt_eq': self.debt_eq,
            'short_float': self.short_float,
            'target_price': self.target_price
        }


def stocks_to_file(file_name):
    data_dir = os.path.join(os.path.curdir, 'data')
    data_path = os.path.join(data_dir, file_name + '.json')

    if not os.path.isdir(data_dir):
        os.mkdir(data_dir)

    output = [stock.output_data() for stock in STOCKS_USD if stock.scrap_data]

    with open(data_path, 'w') as f:
        json.dump(output, f)


def stocks_from_file(file_name):
    data_dir = os.path.join(os.path.curdir, 'data')
    data_path = os.path.join(data_dir, file_name + '.json')

    with open(data_path, 'r') as f:
        input_data = json.load(f)

    for stock in input_data:
        STOCKS_USD.append(stock)


def get_market_stocks(client):
    payload = client.get_market_stocks().payload
    stocks_usd = [stock for stock in payload.instruments[:] if stock.currency == 'USD']
    stocks_rub = [stock for stock in payload.instruments[:] if stock.currency == 'RUB']

    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = [executor.submit(Stock, s.ticker, s.figi, s.isin, s.currency) for s in stocks_usd]
        for future in futures:
            data = future.result()
            if data.scrap_data:
                STOCKS_USD.append(future.result())
        STOCKS_USD.sort()
    stocks_to_file('stocks_usd')


def main():
    keys = {
        "token_tinkoff_real": "",
        "token_tinkoff_demo": ""
    }
    get_all_keys(keys)
    client = tinvest.SyncClient(keys['token_tinkoff_real'])
    stocks_from_file('stocks_usd')


if __name__ == "__main__":
    main()
