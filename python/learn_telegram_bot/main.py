import telebot
import telebot.types
import time
from support import get_token, logging
import stock


print(stock.get_info(stock.MOEX_TICKETS[3]))


# bot = telebot.TeleBot(get_token())
# bot.polling(none_stop=True, interval=0)
#
#
# @bot.message_handler(commands=['help'])
# def send_welcome(message):
#     bot.reply_to(message, "You chose help")
#
#
# @bot.message_handler(commands=['start'])
# def send_welcome(message):
#     bot.reply_to(message, "You chose start")
