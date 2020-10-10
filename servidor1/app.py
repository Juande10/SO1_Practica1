from flask import Flask, request, jsonify, Response
import requests
import json

app = Flask(__name__)

headers = {
    'content-type':'application/json'
}

@app.route('/')
def index():
    return jsonify(
        message='Hola mundo! :)'
    )

def processData(rdata):
    cpu_a = requests.request("GET", "http://35.232.49.94:5000/getCPU")
    ram_a = requests.request("GET", "http://35.232.49.94:5000/getRAM")
    db_a = requests.request("GET", "http://35.232.49.94:5000/getCount")

    valor_cpu_a = int(json.loads(cpu_a.json()['cpu'])['usado'])
    valor_ram_a = int(json.loads(ram_a.json()['cpu'])['MemoriaUsada'])
    valor_cantidad_a = int(db_a.json()['total'])

    cpu_b = requests.request("GET", "http://35.224.249.130:5000/getCPU")
    ram_b = requests.request("GET", "http://35.224.249.130:5000/getRAM")
    db_b = requests.request("GET", "http://35.224.249.130:5000/getCount")

    valor_cpu_b = int(json.loads(cpu_b.json()['cpu'])['usado'])
    valor_ram_b = int(json.loads(ram_b.json()['cpu'])['MemoriaUsada'])
    valor_cantidad_b = int(db_b.json()['total'])

    if valor_cantidad_a > valor_cantidad_b:
        r = requests.request('POST', 'http://35.224.249.130:5000/insert', data = json.dumps(rdata), headers = headers)
    elif valor_cantidad_a < valor_cantidad_b:
        r = requests.request('POST', 'http://35.232.49.94:5000/insert', data = json.dumps(rdata), headers = headers)
    else:
        if valor_ram_a > valor_ram_b:
            r = requests.request('POST', 'http://35.224.249.130:5000/insert', data = json.dumps(rdata), headers = headers)
        elif valor_ram_a < valor_ram_b:
            r = requests.request('POST', 'http://35.232.49.94:5000/insert', data = json.dumps(rdata), headers = headers)
        else:
            if valor_cpu_a > valor_cpu_b:
                r = requests.request('POST', 'http://35.224.249.130:5000/insert', data = json.dumps(rdata), headers = headers)
            elif valor_cpu_a < valor_cpu_b:
                r = requests.request('POST', 'http://35.232.49.94:5000/insert', data = json.dumps(rdata), headers = headers)
            else:
                r = requests.request('POST', 'http://35.232.49.94:5000/insert', data = json.dumps(rdata), headers = headers)

    return {'status' : str(r)}

@app.route('/sendData', methods=['POST'])
def start():
    print(request.json)
    print(json.dumps(request.json)
    res = processData(request.json)
    return Response(response = json.dumps(res), status = 200, mimetype = 'application/json')


if __name__ == '__main__':
    app.run(debug=True, port=5000, host='0.0.0.0')
