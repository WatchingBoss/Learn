from flask import Blueprint

bp = Blueprint('admin', __name__)

from flask_app.admin import routes