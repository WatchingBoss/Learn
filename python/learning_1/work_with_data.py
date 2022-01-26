import os
from datetime import datetime
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def moving_average(df: pd.DataFrame, period: int) -> pd.Series:
    return df['Close'].rolling(window=period, min_periods=period, center=False).mean()


def ma_cross_over_backtest(df):
    t = pd.DataFrame({'Close': df['Close']})
    short_ma = 10
    long_ma = 20
    t['Short_average'] = moving_average(df, short_ma)
    t['Long_average'] = moving_average(df, long_ma)
    t['position_long'] = np.nan
    # t['position_long'] = np.where(t.Short_average > t.Long_average, 1, 0)
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
    print(t1)

    # with pd.ExcelWriter(os.path.join(os.path.curdir, 'data', 'ma_t.xlsx')) as writer:
    #     t.to_excel(writer, sheet_name='sheet_1', index=True)
    #     t1.to_excel(writer, sheet_name='sheet_2', index=True)

    # fig, axs = plt.subplots(2, figsize=(15, 8))
    # axs[0].plot(t['cumpnl_long'])
    # axs[1].plot(t['max_15m_drawdown'])
    # plt.show()


def ma_backtest(df) -> pd.DataFrame:
    short = 10
    long = 20
    df[f'ma{short}'] = moving_average(df, short)
    df[f'ma{long}'] = moving_average(df, long)

    ma_s = f'ma{short}'
    ma_l = f'ma{long}'
    df['position'] = np.where(df[ma_s] > df[ma_l], 1, -1)
    df.dropna(inplace=True)

    df['close_diff'] = df.Close / df.Close.shift(1)
    df['returns'] = np.log(df.Close / df.Close.shift(1))

    df['strategy'] = df['position'].shift(1) * df['returns']

    df['cumsum'] = df['strategy'].cumsum()
    df['cumret'] = df['strategy'].cumsum().apply(np.exp) # Gross perfomance

    df['cummax'] = df['cumret'].cummax()

    drawdown = df['cummax'] - df['cumret']
    print(drawdown.max())

    # TODO: Longest drawdown period

    # print(df[['returns', 'strategy']].mean() * long)                           # Mean return log space
    # print(np.exp(df[['returns', 'strategy']].mean() * long) - 1)               # Mean return regular space
    # print(df[['returns', 'strategy']].std() * long ** 0.5)                     # Standart deviation log space
    # print((df[['returns', 'strategy']].apply(np.exp) - 1).std() * long ** 0.5) # Standart deviation regular space

    return df


def main(df: pd.DataFrame):
    df = ma_backtest(df)
    df = df.drop(columns=['Time', 'Open', 'High', 'Low', 'Volume'])
    print(df.tail(5).to_string())


def get_df(path: str) -> pd.DataFrame:
    df = pd.read_excel(path)
    df = df.drop(columns=df.columns[0])
    df['Time'] = df['Time'].apply(lambda s: datetime.strptime(s, "%d/%m/%y %H:%M:%S"))
    return df


def save_to_h5(path_in, path_out):
    df = get_df(path_in)
    df.to_hdf(path_out, 'data', format='table')


def read_h5(path) -> pd.DataFrame:
    df = pd.DataFrame(pd.read_hdf(path, 'data'))
    return df


FILE_NAME = 'AAPL_15min'
PATH_XLSX = os.path.join('E:', os.sep, 'Document', 'data_to_analys', FILE_NAME + '.xlsx')
PATH_H5 = os.path.join(os.path.curdir, 'data', FILE_NAME + '.h5')

if os.path.isfile(PATH_H5):
    main(read_h5(PATH_H5))
else:
    main(get_df(PATH_XLSX))
    save_to_h5(PATH_XLSX, PATH_H5)
