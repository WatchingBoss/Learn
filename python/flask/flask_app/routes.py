from flask import render_template
from flask_app import app


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
