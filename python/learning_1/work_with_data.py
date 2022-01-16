import os
from datetime import datetime
import pandas as pd


def get_df(path: str) -> pd.DataFrame:
    df = pd.read_excel(path)
    df = df.drop(columns=df.columns[0])
    df['Time'] = df['Time'].apply(lambda s: datetime.strptime(s, "%d/%m/%y %H:%M:%S"))
    return df


def moving_average(df: pd.DataFrame, period: int) -> pd.Series:
    return df['Close'].rolling(window=period, min_periods=period, center=False).mean()


def main(df: pd.DataFrame):
    df['sma20'] = moving_average(df, 20)
    print(df)


PATH = os.path.join('E:', os.sep, 'Document', 'data_to_analys', 'AAPL_15min' + '.xlsx')
main(get_df(PATH))