from bs4 import BeautifulSoup
import requests
from fake_useragent import UserAgent


def check_for_hash(string):
    if len(string) < 2:
        try:
            return float(string)
        except ValueError:
            return 0
    else:
        return float(string)


def check_finviz(ticker):
    header = {'User-Agent': str(UserAgent().chrome)}
    url = f"https://finviz.com/quote.ashx?t={ticker}"
    r = requests.get(url, headers=header)
    soup = BeautifulSoup(r.content, "lxml")

    if not soup.find(id='ticker'):
        return False

    table_title = soup.find('table', class_='fullview-title')

    table_title_trs = table_title.find_all('tr')
    this_ticker = table_title.find(id='ticker').text

    name = table_title_trs[1].text
    sector = table_title_trs[2].find_all('a')[0].text
    industry = table_title_trs[2].find_all('a')[1].text

    table_mult = soup.find('table', class_='snapshot-table2')
    snapshot_td2_cp = table_mult.find_all('td', class_='snapshot-td2-cp')
    snapshot_td2 = table_mult.find_all('td', class_='snapshot-td2')
    mult = {snapshot_td2_cp[i].text.lower(): snapshot_td2[i].text.lower()
            for i in range(len(snapshot_td2))}

    index = mult['index']
    if len(index) < 2:
        index = "None"

    capitalization = mult['market cap']
    cap_multiplication = 1
    if capitalization.find('t'):
        cap_multiplication = 1_000_000_000_000
    elif capitalization.find('b'):
        cap_multiplication = 1_000_000_000
    elif capitalization.find('m'):
        cap_multiplication = 1_000_000
    capitalization = int(check_for_hash(capitalization[0:-1]) * cap_multiplication)

    p_e = check_for_hash(mult['p/e'])
    p_s = check_for_hash(mult['p/s'])
    p_b = check_for_hash(mult['p/b'])
    debt_eq = check_for_hash(mult['debt/eq'])
    short_float = check_for_hash(mult['short float'][0:-1]) / 100
    target_price = check_for_hash(mult['target price'])

    data = {
        'name': name,
        'sector': sector,
        'industry': industry,
        'index': index,
        'capitalization': capitalization,
        'p_e': p_e,
        'p_s': p_s,
        'p_b': p_b,
        'debt_eq': debt_eq,
        'short_float': short_float,
        'target_price': target_price
    }

    if this_ticker == ticker:
        return data
