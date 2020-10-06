import os
from flask import Flask, request, jsonify
from flask_pymongo import PyMongo

application = Flask(__name__)

application.config["MONGO_URI"] = 'mongodb://' + os.environ['MONGODB_USERNAME'] + ':' + os.environ['MONGODB_PASSWORD'] + '@' + os.environ['MONGODB_HOSTNAME'] + ':27017/' + os.environ['MONGODB_DATABASE']

mongo = PyMongo(application)
db = mongo.db

@application.route('/')
def index():
    with open("fake_proc/cpu_201314412", "r+") as f:
        data_cpu=f.read()

    return jsonify(
        status=True,
        cpu=data_cpu,
        data_ram = 666,
        message='Welcome to the Dockerized Flask MongoDB app!'
    )


if __name__ == "__main__":
    ENVIRONMENT_DEBUG = os.environ.get("APP_DEBUG", True)
    ENVIRONMENT_PORT = os.environ.get("APP_PORT", 5000)
    application.run(host='0.0.0.0', port=ENVIRONMENT_PORT, debug=ENVIRONMENT_DEBUG)
