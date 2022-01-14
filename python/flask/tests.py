from datetime import datetime, timedelta
import unittest
from flask_app import app, db
from flask_app.models import User, Post


#TODO: Chapter 15. Better unit test


class UserModelCase(unittest.TestCase):
    def setUp(self):
        app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite://'
        db.create_all()

    def tearDown(self):
        db.session.remove()
        db.drop_all()

    def test_password_hashing(self):
        user = User(username='sara', email='sara@email.com')
        user.set_password('sara123')
        self.assertFalse(user.check_password('123456'))
        self.assertTrue(user.check_password('sara123'))

    def test_avatar(self):
        user = User(username='sara', email='sara@email.com')
        self.assertEqual(user.avatar(64), "https://www.gravatar.com/avatar/"
                                          "a38dcaf670b25385963f80caeeca92dc"
                                          "?d=retro&s=64")

    def test_follow(self):
        user1 = User(username='sara', email='sara@email.com')
        user2 = User(username='rob', email='rob@email.com')
        db.session.add(user1)
        db.session.add(user2)
        db.session.commit()
        self.assertEqual(user1.followed.all(), [])
        self.assertEqual(user1.followers.all(), [])

        user1.follow(user2)
        db.session.commit()
        self.assertTrue(user1.is_following(user2))
        self.assertEqual(user1.followed.count(), 1)
        self.assertEqual(user1.followed.first().username, 'rob')
        self.assertEqual(user2.followers.count(), 1)
        self.assertEqual(user2.followers.first().username, 'sara')

        user1.unfollow(user2)
        db.session.commit()
        self.assertFalse(user1.is_following(user2))
        self.assertEqual(user1.followed.count(), 0)
        self.assertEqual(user2.followers.count(), 0)

    def test_follow_posts(self):
        user1 = User(username='sara', email='sara@email.com')
        user2 = User(username='rob', email='rob@email.com')
        user3 = User(username='mara', email='mara@email.com')
        user4 = User(username='jack', email='jack@email.com')
        db.session.add_all([user1, user2, user3, user4])

        now = datetime.utcnow()
        post1 = Post(body='post from sara', author=user1, timestamp=now - timedelta(seconds=8))
        post2 = Post(body='post from rob', author=user2, timestamp=now - timedelta(seconds=6))
        post3 = Post(body='post from mara', author=user3, timestamp=now - timedelta(seconds=4))
        post4 = Post(body='post from jack', author=user4, timestamp=now - timedelta(seconds=2))
        db.session.add_all([post1, post2, post3, post4])
        db.session.commit()

        user1.follow(user2)
        user1.follow(user4)
        user2.follow(user3)
        user3.follow(user4)

        f1 = user1.followed_posts().all()
        f2 = user2.followed_posts().all()
        f3 = user3.followed_posts().all()
        f4 = user4.followed_posts().all()
        self.assertEqual(f1, [post4, post2, post1])
        self.assertEqual(f2, [post3, post2])
        self.assertEqual(f3, [post4, post3])
        self.assertEqual(f4, [post4])


if __name__ == '__main__':
    unittest.main(verbosity=2)
