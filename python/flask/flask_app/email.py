from flask_mail import Message
from flask_app import mail
from threading import Thread
from flask import current_app


def send_async_mail(app, msg):
    with app.app_context():
        mail.send(msg)


def send_mail(subject, sender, recipients, text_body, html_body):
    msg = Message(subject=subject, sender=sender, recipients=recipients, body=text_body, html=html_body)
    Thread(target=send_async_mail, args=(current_app._get_current_object(), msg)).start()
