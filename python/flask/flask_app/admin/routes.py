from flask import render_template, url_for, current_app
from flask_app import db
from flask_app.admin import bp


@bp.route('/admin/dashboard')
def dashboard():
    return render_template('admin/dashboard.html', title='Admin Dashboard')
