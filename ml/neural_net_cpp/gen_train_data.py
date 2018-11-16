import random

def gen_train_data():
    train_data = "data/in.txt"

    with open(train_data) as train_file:
        train_file.write("topology: 2 4 1")
        for i in range(2000):
            num_1, num_2 = random.randrange(0, 1), random.randrange(0, 1)
            train_file.write("in: {}.0 {}.0\n\
out: {}.0".format(num_1, num_2, num_1 ^ num_2))


if __name__ == "__main__":
    gen_train_data()
