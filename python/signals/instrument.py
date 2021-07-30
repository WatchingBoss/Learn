from datetime import datetime, timedelta, timezone
import asyncio
import scraper
import tinvest
import pandas as pd


class Event:
    pass


class Instrument:
    """
    Exchange instrument imlementation
    """
    def __init__(self, ticker: str, figi: str, isin: str, currency: str):
        self.ticker = ticker
        self.figi = figi
        self.isin = isin
        self.currency = currency


class Timeframe:
    """
    Timeframe implementation
    """

    def __init__(self, interval: tinvest.CandleResolution, delta: timedelta):
        self.candles = pd.DataFrame()

        self.ema = pd.DataFrame()

        self.interval = interval
        self.delta = delta

        self.last_modify_time = datetime.now(tz=timezone.utc)


class Stock(Instrument):
    """
    Stock implementation
    """
    def __init__(self, ticker: str, figi: str, isin: str, currency: str):
        super().__init__(ticker, figi, isin, currency)
        self.data = {}
        self.able_for_short = False

        self.m15: Timeframe = Timeframe(tinvest.CandleResolution.min15, timedelta(days=1))
        self.hour: Timeframe = Timeframe(tinvest.CandleResolution.hour, timedelta(days=7))
        self.day: Timeframe = Timeframe(tinvest.CandleResolution.day, timedelta(days=360))

    def __lt__(self, another):
        return self.ticker < another.ticker

    async def __aiter__(self):
        return self

    def add_scraping_data(self):
        if self.currency == 'USD':
            self.data = scraper.check_finviz(self.ticker)

    def check_if_able_for_short(self):
        self.able_for_short = scraper.check_tinkoff_short_table(self.isin)

    async def ema(self):
        self.m15.ema = ema(self.m15.candles, 'High', 'EMA_10', 10)

    async def detect_intersection(self):
        pass

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


def ema(df: pd.DataFrame, base, target, period, alpha=False):
    con = pd.concat([df[:period][base].rolling(window=period).mean(), df[period:][base]])

    result = pd.DataFrame()

    if alpha:
        # (1 - alpha) * previous_val + alpha * current_val where alpha = 1 / period
        result = con.ewm(alpha=1 / period, adjust=False).mean()
    else:
        # ((current_val - previous_val) * coeff) + previous_val where coeff = 2 / (period + 1)
        result = con.ewm(span=period, adjust=False).mean()

    return result
    # df[target].fillna(0, inplace=True)
    # return df


async def intersection():
    pass


"""
async def detect_intersection_in_timeframe(stock: Stock, tf: inst.Timeframe):
    if tf.ema10_above_20:
        if tf.ema_10 < tf.ema_20:
            tf.ema10_above_20 = False
            send_event(stock.ticker, tf.interval, "EMA 10 under EMA 20")
        else:
            print(f"{stock.ticker}: No intersections")
    else:
        if tf.ema_10 > tf.ema_20:
            tf.ema10_above_20 = True
            send_event(stock.ticker, tf.interval, "EMA 10 above EMA 20")
        else:
            print(f"{stock.ticker}: No intersections")

    if tf.ema50_above_200:
        if tf.ema_50 < tf.ema_200:
            tf.ema50_above_200 = False
            send_event(stock.ticker, tf.interval, "EMA 50 under EMA 200")
        else:
            print(f"{stock.ticker}: No intersections")
    else:
        if tf.ema_50 > tf.ema_200:
            tf.ema50_above_200 = True
            send_event(stock.ticker, tf.interval, "EMA 50 above EMA 200")
        else:
            print(f"{stock.ticker}: No intersections")


async def detect_intersection(stock_dict):
    while True:
        for stock in [stock_dict['BBG00MVWLLM2'], stock_dict['BBG000M65M61'], stock_dict['BBG005P7Q881']]:
            asyncio.create_task(detect_intersection_in_timeframe(stock, stock.m15))
            asyncio.create_task(detect_intersection_in_timeframe(stock, stock.hour))
            asyncio.create_task(detect_intersection_in_timeframe(stock, stock.day))
"""