from datetime import datetime, timedelta, timezone
import asyncio
import scraper
import tinvest


class Instrument:
    """
    Exchange instrument imlementation
    """
    def __init__(self, ticker: str, figi: str, isin: str, currency: str):
        self.ticker = ticker
        self.figi = figi
        self.isin = isin
        self.currency = currency


class Candle:
    """
    Stock candle implementation
    """

    def __init__(self, o: float, l: float, h: float, c: float, v: float, t: datetime):
        self.o = o
        self.l = l
        self.h = h
        self.c = c
        self.v = v
        self.t = t


class Timeframe:
    """
    Timeframe implementation
    """

    def __init__(self, interval, delta):
        self.candles: list[Candle] = []

        self.ema_10: float = 0
        self.ema_20: float = 0
        self.ema_50: float = 0
        self.ema_200: float = 0

        self.ema10_above_20: bool = False
        self.ema50_above_200: bool = False

        self.c_above_10: bool = False
        self.c_above_20: bool = False
        self.c_above_50: bool = False
        self.c_above_200: bool = False

        self.interval = interval
        self.delta: timedelta = delta

        self.last_modify_time: datetime = datetime.now(tz=timezone.utc)


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
