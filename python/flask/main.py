from flask_app import app, db
from flask_app.models import User, Post
from flask_app import cli

@app.shell_context_processor
def make_shell_context():
    return {'db': db, 'User': User, 'Post': Post}