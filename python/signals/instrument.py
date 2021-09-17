from datetime import datetime, timedelta, timezone
import asyncio
import scraper
import tinvest
import pandas as pd
import tradingview_ta as tvta


SIGNAL = []


class Instrument:
    """
    Exchange instrument imlementation
    """
    def __init__(self, ticker: str, figi: str, isin: str, currency: str):
        self.ticker = ticker
        self.figi = figi
        self.isin = isin
        self.currency = currency


class TradingviewTF:
    """
    Timeframe for data from tradingview
    """
    def __init__(self, ticker: str, interval: tvta.Interval):
        self.ticker = ''
        self.interval = interval
        self.sum = {'sum': '', 'ma': '', 'osc': ''}
        self.ema = {'ema10': '', 'ema20': '', 'ema50': '', 'ema200': '', }
        self.osc = {'momentum': '', 'macd': ''}
        self.val = {'o': 0, 'h': 0, 'l': 0, 'c': 0}
        self.macd_val = 0


class Timeframe:
    """
    Timeframe implementation
    """

    def __init__(self, interval: tinvest.CandleResolution, delta: timedelta):
        self.candles = pd.DataFrame()

        self.indicators = pd.DataFrame()

        self.interval = interval
        self.delta = delta

        self.last_modify_time = datetime.now(tz=timezone.utc)

    def ema(self):
        self.candles = EMA(self.candles, 'Close', 'ema_10', 10, False)


class Event:
    def __init__(self, tf: TradingviewTF, msg):
        self.tf = tf
        self.msg = msg


def update_tvtf(tf: TradingviewTF, prev_dict, new_dict):
    for k, v in new_dict.items():
        if prev_dict[k] != v:
            prev_dict[k] = v
            if v == 'BUY' or v == 'STRONG BUY' and prev_dict[k] != 'STRONG BUY':
                msg = f"{tf.ticker}\n" \
                      f"Interval: {tf.interval}\n" \
                      f"{k}: {v}"
                SIGNAL.append(Event(tf, msg))


class Stock(Instrument):
    """
    Stock implementation
    """
    def __init__(self, ticker: str, figi: str, isin: str, currency: str):
        super().__init__(ticker, figi, isin, currency)
        self.data = {}
        self.able_for_short = False

        self.m15 = Timeframe(tinvest.CandleResolution.min15, timedelta(days=1))
        self.hour = Timeframe(tinvest.CandleResolution.hour, timedelta(days=7))
        self.day = Timeframe(tinvest.CandleResolution.day, timedelta(days=360))

        self.tv_hour = TradingviewTF(self.ticker, tvta.Interval.INTERVAL_1_HOUR)
        self.tv_day = TradingviewTF(self.ticker, tvta.Interval.INTERVAL_1_DAY)

    def __lt__(self, another):
        return self.ticker < another.ticker

    async def __aiter__(self):
        return self

    def add_scraping_data(self):
        if self.currency == 'USD':
            self.data = scraper.check_finviz(self.ticker)

    def check_if_able_for_short(self):
        self.able_for_short = scraper.check_tinkoff_short_table(self.isin)

    def get_tradingview_data(self):
        for tf in [self.tv_hour, self.tv_day]:
            data = tvta.TA_Handler(
                symbol=self.ticker,
                screener="america",
                exchange=self.data['exchange'],
                interval=tf.interval
            ).get_analysis()

            this_sum = {'sum': data.summary['RECOMMENDATION'],
                        'ma': data.moving_averages['RECOMMENDATION'],
                        'osc': data.oscillators['RECOMMENDATION']}
            x = data.moving_averages['COMPUTE']
            this_ema = {'ema10': x['EMA10'], 'ema20': x['EMA20'],
                        'ema50': x['EMA50'], 'ema200': x['EMA200']}
            x = data.oscillators['COMPUTE']
            this_osc = {'momentum': x['Mom'], 'macd': x['MACD']}

            x = data.indicators
            this_macd_val = float(x['MACD.macd']) - float(x['MACD.signal'])
            this_ohlc = {'o': x['open'], 'h': x['high'], 'l': x['low'], 'c': x['close']}

            update_tvtf(tf, tf.sum, this_sum)
            update_tvtf(tf, tf.ema, this_ema)
            update_tvtf(tf, tf.osc, this_osc)

    def output_data(self, level):
        base_data = {
            'ticker': self.ticker,
            'figi': self.figi,
            'isin': self.isin,
            'currency': self.currency
        }
        if level == 2:
            return base_data.update(self.data)
        elif level == 1:
            return base_data


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


def EMA(df, base, target, period, alpha=False):
    """
    Function to compute Exponential Moving Average (EMA)

    Args :
        df : Pandas DataFrame which contains ['date', 'open', 'high', 'low', 'close', 'volume'] columns
        base : String indicating the column name from which the EMA needs to be computed from
        target : String indicates the column name to which the computed data needs to be stored
        period : Integer indicates the period of computation in terms of number of candles
        alpha : Boolean if True indicates to use the formula for computing EMA using alpha (default is False)

    Returns :
        df : Pandas DataFrame with new column added with name 'target'
    """

    con = pd.concat([df[:period][base].rolling(window=period).mean(), df[period:][base]])

    if (alpha == True):
        # (1 - alpha) * previous_val + alpha * current_val where alpha = 1 / period
        df[target] = con.ewm(alpha=1 / period, adjust=False).mean()
    else:
        # ((current_val - previous_val) * coeff) + previous_val where coeff = 2 / (period + 1)
        df[target] = con.ewm(span=period, adjust=False).mean()

    df[target].fillna(0, inplace=True)
    return df


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