from flask import render_template, flash, redirect, url_for
from flask_app import app
from flask_app.forms import LoginForm


@app.route('/login', methods=['GET', 'POST'])
def login():
    form = LoginForm()
    if form.validate_on_submit():
        flash(f'Login requisted for user {form.username.data}, remember_me={form.remember_me.data}')
        return redirect(url_for('index'))
    return render_template('login.html', title='Sign in', form=form)


@app.route('/')
@app.route('/index')
def index():
    user = {'name': 'John',
            'age': 25}

    phones = [
        {
            'manufacturer': 'Xiaomi',
            'model': 'Redmi 9',
            'price': 12_490,
            'currency': 'RUR'
        },
        {
            'manufacturer': 'Apple',
            'model': 'iPhone 11',
            'price': 50_880,
            'currency': 'RUR'
        },
        {
            'manufacturer': 'Samsung',
            'model': 'Galaxy A12',
            'price': 11_590,
            'currency': 'RUR'
        }
    ]

    return render_template('index.html', title='Home', user=user, phones=phones)
