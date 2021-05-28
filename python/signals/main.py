import os, datetime, sys, json
import tinvest
from bs4 import BeautifulSoup
import requests
from fake_useragent import UserAgent

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

    def add_scraping_data(self):
        if self.currency == 'USD':
            pass
        elif self.currency == 'RUB':
            pass
        elif self.currency == 'EUR':
            pass
        else:
            pass


def get_market_stocks(client):
    payload = client.get_market_stocks().payload
    total_stocks = payload.total
    stocks_usd = [stock for stock in payload.instruments[:] if stock.currency == 'USD']
    stocks_rub = [stock for stock in payload.instruments[:] if stock.currency == 'RUB']
    # for stock in stocks_usd:
    #     STOCKS_USD.append(Stock(stock.ticker, stock.figi, stock.isin, stock.currency))
    # for stock in stocks_rub:
    #     STOCKS_RUB.append(Stock(stock.ticker, stock.figi, stock.isin, stock.currency))

    check_finviz(stocks_usd[3].ticker)


def check_finviz(ticker):
    # url = f"https://finviz.com/quote.ashx?t={ticker}"
    # ua = UserAgent()
    # header = {'User-Agent': str(ua.chrome)}
    # r = requests.get(url, headers=header)
    with open('temp.html', 'r', encoding='utf-8') as f:
        soup = BeautifulSoup(f, "lxml")

    table_title = soup.find('table', class_='fullview-title')

    table_title_trs = table_title.find_all('tr')
    page_ticker = table_title.find(id='ticker').text
    print(page_ticker)
    exchange = table_title_trs[0].find(class_='body-table').text
    if exchange.find('NASD'):
        exchange = 'NASDAQ'
    elif exchange.find('NYSE'):
        exchange = 'NYSE'
    print(exchange)
    name = table_title_trs[1].text
    print(name)
    sector = table_title_trs[2].find_all('a')[0].text
    industrial = table_title_trs[2].find_all('a')[1].text
    print(f"{sector}\n{industrial}")

    table_mult = soup.find('table', class_='snapshot-table2')
    snapshot_td2_cp = table_mult.find_all('td', class_='snapshot-td2-cp')
    snapshot_td2 = table_mult.find_all('td', class_='snapshot-td2')
    mult = {snapshot_td2_cp[i].text.lower(): snapshot_td2[i].text.lower()
            for i in range(len(snapshot_td2))}
    for k, v in mult.items():
        print(f"{k}: {v}")


def main():
    keys = {
        "token_tinkoff_real": "",
        "token_tinkoff_demo": ""
    }
    get_all_keys(keys)
    client = tinvest.SyncClient(keys['token_tinkoff_real'])
    get_market_stocks(client)


if __name__ == "__main__":
    main()
