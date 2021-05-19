import json
import pprint


def get_token():
    with open("private_info.json", "r") as file:
        info = json.loads(file.read())
    return info['token']


def logging(msg):
    print(msg)
    pprint.pprint(msg)
