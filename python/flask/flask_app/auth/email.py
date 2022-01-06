from flask import render_template, current_app
from flask_babel import gettext as  _
from flask_app.email import send_mail


def send_password_reset_email(user):
    token = user.get_reset_password_token()
    send_mail(_('Reset your password'), current_app.config['ADMINS'][0], [user.email],
              render_template('email/reset_password.txt', user=user, token=token),
              render_template('email/reset_password.html', user=user, token=token))