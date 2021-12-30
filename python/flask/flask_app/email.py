from flask import render_template
from flask_mail import Message
from flask_app import app, mail
from flask_app.models import User
from threading import Thread


def send_async_mail(current_app, msg):
    with current_app.app_context():
        mail.send(msg)


def send_mail(subject, sender, recipients, text_body, html_body):
    msg = Message(subject=subject, sender=sender, recipients=recipients, body=text_body, html=html_body)
    Thread(target=send_async_mail, args=(app, msg)).start()


def send_password_reset_email(user: User):
    token = user.get_reset_password_token()
    send_mail('Reset your password', app.config['ADMINS'][0], [user.email],
              render_template('email/reset_password.txt', user=user, token=token),
              render_template('email/reset_password.html', user=user, token=token))
