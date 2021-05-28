import os, time, sys, json
import tinvest

KEYS = {
    "token_tinkoff_real": "",
    "token_tinkoff_demo": ""
}


def get_all_keys():
    with open(os.path.join(os.path.expanduser('~'), 'no_commit', 'info.json')) as f:
        data = json.load(f)
        ttr = data['token_tinkoff_real']
        ttd = data['token_tinkoff_demo']
        KEYS['token_tinkoff_real'] = ttr
        KEYS['token_tinkoff_demo'] = ttd


get_all_keys()
client = tinvest.SyncClient(KEYS['token_tinkoff_real'])


def show_get_portfolio():
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


def show_get_portfolio_currencies():
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


def show_get_orders():
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


def main():
    show_get_orders()


if __name__ == "__main__":
    main()
