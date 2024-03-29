import os

basedir = os.path.abspath(os.path.dirname(__file__))
#TODO: Using load_dotenv to load variables from .env file in basedir

class Config(object):
    SECRET_KEY = os.environ.get('SECRET_KEY') or 'this_is_hardcoded_string'
    SQLALCHEMY_DATABASE_URI = os.environ.get('DATABASE_URL') or f"sqlite:///{os.path.join(basedir, 'app.db')}"
    SQLALCHEMY_TRACK_MODIFICATIONS = False
    POSTS_PER_PAGE = 10
    MAIL_SERVER = os.environ.get('MAIL_SERVER') or 'localhost'
    MAIL_PORT = int(os.environ.get('MAIL_PORT') or 8025)
    # MAIL_USE_TLS = os.environ.get('MAIL_USE_TLS') is not None
    # MAIL_USERNAME = os.environ.get('MAIL_USERNAME')
    # MAIL_PASSWORD = os.environ.get('MAIL_PASSWORD')
    ADMINS = os.environ.get('ADMINS') or ['admin@email.com']
    LANGUAGES = ['en', 'ru']
    ELASTICSEARCH_URL = os.environ.get('ELASTICSEARCH_URL')
