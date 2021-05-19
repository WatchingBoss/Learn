from bs4 import BeautifulSoup
import requests

MOEX_TICKETS = ["AFKS", "AFLT", "CBOM", "CHMF", "DSKY", "FEES", "FINE", "GAZP", "GMKN", "HYDR", "IRAO", "LKOH"]


def get_info(ticket):
    url = f"https://www.moex.com/ru/issue.aspx?board=TQBR&code={ticket}"
    page = requests.get(url)
    soup = BeautifulSoup(page.text, "html.parser")



    return f""
