import os
from datetime import datetime
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def get_df(path: str) -> pd.DataFrame:
    df = pd.read_excel(path)
    df = df.drop(columns=df.columns[0])
    df['Time'] = df['Time'].apply(lambda s: datetime.strptime(s, "%d/%m/%y %H:%M:%S"))
    return df


def moving_average(df: pd.DataFrame, period: int) -> pd.Series:
    return df['Close'].rolling(window=period, min_periods=period, center=False).mean()


def ma_cross_over_backtest(df):
    t = pd.DataFrame({'Close': df['Close']})
    short_ma = 10
    long_ma = 20
    t['Short_average'] = t['Close'].rolling(window=short_ma, min_periods=short_ma, center=False).mean()
    t['Long_average'] = t['Close'].rolling(window=long_ma, min_periods=short_ma, center=False).mean()
    t['position_long'] = np.nan
    for x in range(len(t)):
        if t.Short_average[x] > t.Long_average[x]:
            t['position_long'][x] = 1
        if t.Short_average[x] < t.Long_average[x]:
            t['position_long'][x] = 0
    t.position_long = t.position_long.fillna(method='ffill')
    t['Price_difference'] = t.Close - t.Close.shift(1)
    t['pnllong'] = t.position_long.shift(1) * t.Price_difference
    t['cumpnl_long'] = t.pnllong.cumsum()

    t['rolling_max'] = t['cumpnl_long'].rolling(250, min_periods=1).max()
    t['15m_drawdown'] = t['cumpnl_long'] - t['rolling_max']
    t['max_15m_drawdown'] = t['15m_drawdown'].rolling(250, min_periods=1).min()

    t['Trade'] = t['position_long'].diff()
    t1 = t.where((t.Trade != 0))
    t1 = t1.dropna()
    t1.drop(['Short_average', 'Long_average', 'position_long', 'Price_difference', 'pnllong',
             'rolling_max', '15m_drawdown', 'max_15m_drawdown'], axis=1, inplace=True)
    t1['Trade_return'] = (t1['cumpnl_long'].diff() / t1['Close']) * 100

    print(f"Number of trade count: {round(len(t1) / 2)}")

    with pd.ExcelWriter(os.path.join(os.path.curdir, 'data', 'ma_t.xlsx')) as writer:
        t.to_excel(writer, sheet_name='sheet_1', index=True)
        t1.to_excel(writer, sheet_name='sheet_2', index=True)

    # fig, axs = plt.subplots(2, figsize=(15, 8))
    # axs[0].plot(t['cumpnl_long'])
    # axs[1].plot(t['max_15m_drawdown'])
    # plt.show()


def main(df: pd.DataFrame):
    ma_cross_over_backtest(df)


PATH = os.path.join('E:', os.sep, 'Document', 'data_to_analys', 'AAPL_15min' + '.xlsx')
main(get_df(PATH))