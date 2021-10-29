from flask import Flask, render_template

app = Flask(__name__)


@app.route('/')
def home_page():
    return render_template('home.html')


@app.route('/about')
def about_page():
    page = "<p style='font-size:20px; color:magenta';>This is about page</p>"
    return page


@app.route('/about/<username>')
def about_page_user(username):
    page = f"<p style='font-size:20px; color:magenta';>This is about page of {username}</p>"
    return page


if __name__ == '__main__':
    app.run()
