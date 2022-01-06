from flask import render_template, flash, redirect, url_for, request, g, jsonify, current_app
from flask_app import db
from flask_app.main import bp
import flask_app.main.forms as forms
from flask_login import current_user, login_required
from flask_app.models import User, Post
from datetime import datetime
from flask_babel import gettext as _, get_locale


@bp.route('/translate', methods=['POST'])
@login_required
def translate():
    text = f"Translation of post with id {request.get_json()['post_id']}"
    return jsonify({'text': text})


@bp.route('/follow/<username>', methods=['POST'])
@login_required
def follow(username):
    form = forms.EmptyForm()
    if form.validate_on_submit():
        user = User.query.filter_by(username=username).first()
        if user is None:
            flash(_("There is no %(username)s user", username=username))
            return redirect(url_for('index'))
        if user == current_user:
            flash(_("You cannot follow yourself"))
            return redirect(url_for('profile', username=username))
        current_user.follow(user)
        db.session.commit()
        flash(_(f"Now you following %(username)s user", username=username))
        return redirect(url_for('profile', username=username))
    else:
        return redirect(url_for('index'))


@bp.route('/unfollow/<username>', methods=['POST'])
@login_required
def unfollow(username):
    form = forms.EmptyForm()
    if form.validate_on_submit():
        user = User.query.filter_by(username=username).first()
        if user is None:
            flash(_(f"There is no %(username)s user", username=username))
            return redirect(url_for('index'))
        if user == current_user:
            flash(_("You cannot unfollow yourself"))
            return redirect(url_for('profile', username=username))
        current_user.unfollow(user)
        db.session.commit()
        flash(_(f"Now you not following %(username)s user", username=username))
        return redirect(url_for('profile', username=username))
    else:
        return redirect(url_for('index'))


@bp.route('/edit_profile', methods=['GET', 'POST'])
@login_required
def edit_profile():
    form = forms.EditProfileForm(current_user.username)
    if form.validate_on_submit():
        current_user.username = form.username.data
        current_user.about_me = form.about_me.data
        db.session.commit()
        flash(_('Your changes have been saved'))
        return redirect(url_for('edit_profile'))
    elif request.method == 'GET':
        form.username.data = current_user.username
        form.about_me.data = current_user.about_me
    return render_template('edit_profile.html', title='Edit Profile', form=form)


@bp.route('/profile/<username>')
@login_required
def profile(username):
    user = User.query.filter_by(username=username).first_or_404()
    page = request.args.get('page', 1, type=int)
    posts = user.posts.order_by(Post.timestamp.desc())\
                .paginate(page, current_app.config['POSTS_PER_PAGE'], False)
    next_url = url_for('profile', username=user.username, page=posts.next_num) if posts.has_next else None
    prev_url = url_for('profile', username=user.username, page=posts.prev_num) if posts.has_prev else None
    form = forms.EmptyForm()
    return render_template('profile.html', title='Profile', user=user, posts=posts.items, form=form,
                           next_url=next_url, prev_url=prev_url)


@bp.before_request
def before_request():
    if current_user.is_authenticated:
        current_user.last_seen = datetime.utcnow()
        db.session.commit()
    g.locale = str(get_locale())


@bp.route('/explore')
@login_required
def explore():
    page = request.args.get('page', 1, type=int)
    posts = Post.query.order_by(Post.timestamp.desc())\
                .paginate(page, current_app.config['POSTS_PER_PAGE'], False)
    next_url = url_for('explore', page=posts.next_num) if posts.has_next else None
    prev_url = url_for('explore', page=posts.prev_num) if posts.has_prev else None
    return render_template('index.html', title='Home', posts=posts.items, next_url=next_url, prev_url=prev_url)


@bp.route('/', methods=["GET", "POST"])
@bp.route('/index', methods=["GET", "POST"])
@login_required
def index():
    form = forms.PostForm()
    if form.validate_on_submit():
        post = Post(body=form.post.data, author=current_user)
        db.session.add(post)
        db.session.commit()
        flash(_("You post is live now"))
        return redirect(url_for('index'))
    page = request.args.get('page', 1, type=int)
    posts = current_user.followed_posts()\
            .paginate(page, current_app.config['POSTS_PER_PAGE'], False)
    next_url = url_for('index', page=posts.next_num) if posts.has_next else None
    prev_url = url_for('index', page=posts.prev_num) if posts.has_prev else None
    return render_template('index.html', title='Home', form=form, posts=posts.items,
                           next_url=next_url, prev_url=prev_url)
