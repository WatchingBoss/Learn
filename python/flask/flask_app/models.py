from datetime import datetime
from flask_app import db, login
from werkzeug.security import generate_password_hash, check_password_hash
from flask_login import UserMixin
from hashlib import md5
from urllib.parse import urlencode


followers = db.Table('followers',
                     db.Column('follower_id', db.Integer, db.ForeignKey('user.id')),
                     db.Column('followed_id', db.Integer, db.ForeignKey('user.id'))
)


class User(db.Model, UserMixin):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(64), index=True, unique=True)
    email = db.Column(db.String(120), index=True, unique=True)
    password_hash = db.Column(db.String(128))
    about_me = db.Column(db.String(140))
    last_seen = db.Column(db.DateTime, default=datetime.utcnow())
    posts = db.relationship('Post', backref='author', lazy='dynamic')
    followed = db.relationship('User', secondary=followers,
                               primaryjoin=(followers.columns.follower_id == id),
                               secondaryjoin=(followers.columns.followed_id == id),
                               backref=db.backref('followers', lazy='dynamic'), lazy='dynamic')

    def __repr__(self):
        return f"<User {self.username}>"

    def set_password(self, password):
        self.password_hash = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)

    def avatar(self, size):
        return f"https://www.gravatar.com/avatar/{md5(self.email.lower().encode('utf-8')).hexdigest()}?" \
               f"{urlencode({'d': 'retro', 's': size})}"

    def is_following(self, user):
        return self.followed.filter(followers.columns.followed_id == user.id).count() > 0

    def follow(self, user):
        if not self.is_following(user):
            self.followed.append(user)

    def unfollow(self, user):
        if self.is_following(user):
            self.followed.remove(user)

    def followed_posts(self):
        followed = Post.query.join(followers, (followers.columns.followed_id == Post.user_id))\
                             .filter(followers.columns.follower_id == self.id)
        own = Post.query.filter_by(user_id=self.id)
        return followed.union(own).order_by(Post.timestamp.desc())


class Post(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    body = db.Column(db.String(140))
    timestamp = db.Column(db.DateTime, index=True, default=datetime.utcnow)
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'))

    def __repr__(self):
        return f"<Post {self.body}>"


@login.user_loader
def load_user(id):
    return User.query.get(int(id))
