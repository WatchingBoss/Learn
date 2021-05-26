from bs4 import BeautifulSoup
from selenium import webdriver
import requests
import re
import time
import os
import json
import threading

MOEX_TICKERS = ['AFKS',  'AFLT',  'ALRS',  'CBOM',  'CHMF',  'DSKY',  'FEES',  'FIVE',  'GAZP',  'GMKN',  'HYDR',
                'IRAO',  'LKOH',  'LSRG',  'MAGN',  'MAIL',  'MGNT',  'MOEX',  'MTSS',  'NLMK',  'NVTK',  'PHOR',
                'PIKK',  'PLZL',  'POGR',  'POLY',  'QIWI',  'ROSN',  'RSTI',  'RTKM',  'RUAL',  'SBER',  'SBERP',
                'SNGS',  'SNGSP',  'TATN',  'TATNP',  'TCSG',  'TRNFP',  'UPRO',  'VTBR',  'YNDX']
USING_PARSER_BS4 = "lxml"

MOEX_PATH = 'moex_stocks.json'


def get_tickers():
    url = "https://www.tradingview.com/symbols/MOEX-IMOEX/components/"
    page = requests.get(url)
    soup = BeautifulSoup(page.text, USING_PARSER_BS4)

    links = soup.find_all('a', class_="tv-screener__symbol")
    for link in links:
        if len(link.string) < 6:
            print(f"'{link.string}'", end=",  ")


def get_info(driver, ticker):
    url = f"https://www.moex.com/ru/issue.aspx?board=TQBR&code={ticker}"
    driver.get(url)
    soup = BeautifulSoup(driver.page_source, USING_PARSER_BS4)

    # with open("moex_sber.html", encoding="utf8") as file:
    #     soup = BeautifulSoup(file, "lxml")

    stock_info = {}

    all_tr = soup.find(id='description_container').find_all('tr')
    stock_info['short_name'] = all_tr[1].td.string
    stock_info['full_name'] = all_tr[2].td.string

    nums = []
    for li in soup.find(id='digest_container').find_all('li'):
        nums.append(re.findall(r"[-+]?\d*\.\d+|\d+", li.text.replace(',', '.').replace(' ', '')))

    nums[1][0].replace('+', '-')

    stock_info['price'] = float(nums[0][0])
    stock_info['change'] = float(nums[1][0])
    stock_info['max'] = float(nums[3][0])
    stock_info['min'] = float(nums[3][1])
    stock_info['trades'] = int(nums[4][0])
    stock_info['volume'] = int(nums[4][1])
    stock_info['last_update'] = time.strftime("%H : %M : %S", time.localtime())

    return stock_info


def telegram_get_stock_info(ticker):
    if os.path.isfile(MOEX_PATH):
        with open(MOEX_PATH) as f:
            data = json.load(f)
            if data[ticker]:
                return data[ticker]
            else:
                return False
    else:
        return False


def fill_data():
    while True:
        print(f"Start updating at {time.strftime('%H:%M:%S', time.localtime())}")
        stocks = {}

        options = webdriver.ChromeOptions()
        options.add_argument('headless')
        with webdriver.Chrome() as driver:
            for ticker in MOEX_TICKERS:
                stocks[ticker] = get_info(driver, ticker)

        with open(MOEX_PATH, 'w') as f:
            f.write(json.dumps(stocks))

        print(f"Updating done at {time.strftime('%H:%M:%S', time.localtime())}")

        time.sleep(600)


def test():
    t = threading.Thread(target=fill_data)
    t.start()
    for i in range(10):
        for ticker in MOEX_TICKERS:
            info = telegram_get_stock_info(ticker)
            try:
                print(f"Краткое наименование: {info['short_name']}\n"
                      f"Полное наименование: {info['full_name']}\n"
                      f"Последняя цена: {info['price']}\n"
                      f"Изменеие за день: {info['change']}\n"
                      f"Максимальная цена за день: {info['max']}\n"
                      f"Минимальная цена за день: {info['min']}\n"
                      f"Количество сделок за день: {info['trades']}\n"
                      f"Объем сделок (рубли): {info['volume']}\n")
                print("\n\n")
            except:
                print(f"Problem: {i}")
        i += 1
        time.sleep(10)


# def main():
#     options = webdriver.ChromeOptions()
#     options.add_argument('headless')
#     wb = xlwt.Workbook()
#     ws = wb.add_sheet('stocks')
#
#     ws.write(0, 0, "ticker")
#     ws.write(0, 1, "Short name")
#     ws.write(0, 2, "Full name")
#     ws.write(0, 3, "Price")
#     ws.write(0, 4, "Change")
#     ws.write(0, 5, "Max for today")
#     ws.write(0, 6, "Min for today")
#     ws.write(0, 7, "Trades today")
#     ws.write(0, 8, "Volume today")
#
#     current_row = 1
#     with webdriver.Chrome() as driver:
#         for ticker in MOEX_TICKERS:
#             info = get_info(driver, ticker)
#             print(f"Краткое наименование: {info['short_name']}\n"
#                   f"Полное наименование: {info['full_name']}\n"
#                   f"Последняя цена: {info['price']}\n"
#                   f"Изменеие за день: {info['change']}\n"
#                   f"Максимальная цена за день: {info['max']}\n"
#                   f"Минимальная цена за день: {info['min']}\n"
#                   f"Количество сделок за день: {info['trades']}\n"
#                   f"Объем сделок (рубли): {info['volume']}\n")
#             print("\n\n")
#
#             ws.write(current_row, 0, ticker)
#             ws.write(current_row, 1, info['short_name'])
#             ws.write(current_row, 2, info['full_name'])
#             ws.write(current_row, 3, info['price'])
#             ws.write(current_row, 4, info['change'])
#             ws.write(current_row, 5, info['max'])
#             ws.write(current_row, 6, info['min'])
#             ws.write(current_row, 7, info['trades'])
#             ws.write(current_row, 8, info['volume'])
#
#             current_row += 1
#
#     wb.save('file.xls')
