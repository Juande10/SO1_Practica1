import os
import json
from flask import Flask, request, jsonify
from flask_pymongo import PyMongo
from pymongo import MongoClient


application = Flask(__name__)

class MongoApi:
    def __init__(self, data):
        self.client = MongoClient("mongodb://mongodb:27017")

#application.config["MONGO_URI"] = 'mongodb://' + os.environ['MONGODB_USERNAME'] + ':' + os.environ['MONGODB_PASSWORD'] + '@' + os.environ['MONGODB_HOSTNAME'] + ':27017/' + os.environ['MONGODB_DATABASE']

#mongo = PyMongo(application)
#db = mongo.db

client = MongoClient("mongodb://mongodb:27017")
db = client["sope1db"]
col = db["oraciones"]

@application.route('/')
def index():
    with open("fake_proc/cpu_201314412", "r+") as f:
        data_cpu=f.read()

    with open("fake_proc/ram_201314412", "r+") as f:
        data_ram = f.read()

    data = request.json
    contador = col.find().count()

    return jsonify(
        total = contador,
        status=True,
        data_cpu=data_cpu,
        data_ram = data_ram,
        message='Welcome to the Dockerized Flask MongoDB app!'
    )

@application.route('/getCPU')
def getServerCPU():
    with open("fake_proc/cpu_201314412", "r+") as f:
        data_cpu = f.read()

    data = request.json
    contador = col.find().count()

    return jsonify(
        cpu=data_cpu
    )

@application.route('/getRAM')
def getServerRAM():
    with open("fake_proc/ram_201314412", "r+") as f:
        data_ram = f.read()

    return jsonify(
        cpu=data_ram 
    )

@application.route('/insert', methods=['POST'])
def insertData():
   data = request.get_json()
   col.insert({'autor':data['autor'], 'nota':data['nota']})
   #col.insert(json.dumps(data))
   return data['autor']


@application.route('/insertar1')
def insert1():
    #print(db)
    #doc = db.sopes1db.insert({'autor':'juanito', 'nota':'nota de prueba'})
    col.insert({'autor':'juanito', 'nota':'nota de prueba'})
    return "Inserted"

if __name__ == "__main__":
    ENVIRONMENT_DEBUG = os.environ.get("APP_DEBUG", True)
    ENVIRONMENT_PORT = os.environ.get("APP_PORT", 5000)
    application.run(host='0.0.0.0', port=ENVIRONMENT_PORT, debug=ENVIRONMENT_DEBUG)
