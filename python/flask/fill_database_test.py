from datetime import datetime
from flask_app import db, app
from flask_app.models import User, Post


def fill_db():
    u1 = User(username='John', email='john@email.com')
    u2 = User(username='Rob', email='rob@email.com')
    u3 = User(username='Sara', email='sara@email.com')
    u4 = User(username='Mary', email='mary@email.com')
    u5 = User(username='Piter', email='piter@email.com')

    users = [u1, u2, u3, u4, u5]

    db.session.add_all(users)
    db.session.commit()

    for u in users:
        u.set_password(u.username.lower())
        u.last_seen = datetime.utcnow()
        u.about_me = f"This is bio of {u.username}"

        ci = users.index(u)
        u.follow(users[ci-1])
        u.follow(users[ci-2])

        for i in range(1, 4):
            db.session.add(Post(body=f"Port from {u.username} #{i}",
                                author=u, timestamp=datetime.utcnow()))
        db.session.commit()


if __name__ == '__main__':
    fill_db()