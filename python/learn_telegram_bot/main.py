import telebot
from telebot import types
import time
from support import get_token, logging
import stock
import threading


update_stocks_base = threading.Thread(target=stock.fill_data)
update_stocks_base.start()


bot = telebot.TeleBot(get_token())

# Main menu
menu_keyboard = types.InlineKeyboardMarkup()
menu_keyboard.add(types.InlineKeyboardButton(text="Получить данные акции", callback_data="stocks"))

# Menu to choose ticket of stock
stocks_keyboard = types.InlineKeyboardMarkup()
for ticker in stock.MOEX_TICKERS:
    stocks_keyboard.add(types.InlineKeyboardButton(text=f"{ticker}", callback_data=f"ticker_{ticker}"))


@bot.message_handler(commands=['start'])
def send_welcome(message):
    logging(message)
    bot.send_message(message.from_user.id, "Стартуем")


@bot.message_handler(commands=['help'])
def send_help(message):
    logging(message)
    bot.send_message(message.from_user.id,
                     f"/help - Вызвать это сообщение\n"
                     f"/start - Стартануть\n"
                     f"/menu - Вызвать главное меню")


@bot.message_handler(commands=['menu'])
def send_menu(message):
    logging(message)
    bot.send_message(message.from_user.id, text="Выбери действие", reply_markup=menu_keyboard)


@bot.message_handler(content_types=['text'])
def send_message(message):
    logging(message)
    bot.send_message(message.from_user.id, "Обычный текст не канает")
    bot.send_message(message.from_user.id, text="Выбери действие", reply_markup=menu_keyboard)


@bot.callback_query_handler(func=lambda call: True)
def callback_worker(call):
    logging(call)
    if call.data == "stocks":
        bot.send_message(call.message.chat.id, text="Выбери акцию", reply_markup=stocks_keyboard)
    if call.data.startswith("ticker"):
        this_ticker = call.data[7:]
        info = stock.telegram_get_stock_info(this_ticker)
        print(info)
        if info:
            msg = f"Тикер: {this_ticker}\n" \
                  f"Краткое наименование: {info['short_name']}\n" \
                  f"Полное наименование: {info['full_name']}\n" \
                  f"Последняя цена: {info['price']}\n" \
                  f"Изменеие за день: {info['change']}\n" \
                  f"Максимальная цена за день: {info['max']}\n" \
                  f"Минимальная цена за день: {info['min']}\n" \
                  f"Количество сделок за день: {info['trades']}\n" \
                  f"Объем сделок (рубли): {info['volume']}\n" \
                  f"Последнее обновление: {info['last_update']}"
        else:
            msg = "Stocks base is not ready yet"

        bot.send_message(call.message.chat.id, msg)


bot.polling(none_stop=True, interval=0)
