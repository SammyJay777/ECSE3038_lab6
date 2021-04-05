from flask import Flask, request, jsonify, json
from flask_pymongo import PyMongo
from marshmallow import Schema, fields, ValidationError
from bson.json_util import dumps
from json import loads
from datetime import datetime

app = Flask(__name__)
app.config["MONGO_URI"] = "mongodb+srv://User620119624:Student_620119624@cluster-620119624.gb5bm.mongodb.net/Tank?retryWrites=true&w=majority"
mongo = PyMongo(app)

ClientData = {
    "tank_id": "t1",
    "percentage_full": 12
}

class Level(Schema):
    tank_id = fields.String(required=True)
    percentage_full = fields.Integer(required=True)

def percent(x, in_min, in_max, out_min, out_max):
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)


#@app.route("/tank")
#def get_tanks():
#  Tank01 = mongo.db.Tank01.find()
#  return jsonify(loads(dumps(Tank01)))

@app.route("/tank", methods=["POST"])
def add_tank():
    W_level = (request.json["water_level"])
    P_full = percent(W_level, 10, 200, 0, 100)
    ClientData["tank_id"] = request.json["tank_id"]
    ClientData["percentage_full"] = P_full
    try:
        C_Data = Level().load(ClientData)
        clientUP = mongo.db.levels.insert_one(C_Data).inserted_id
        clientDN = mongo.db.levels.find_one(clientUP)
        # return loads(dumps(clientDN))
        # Get date and time
        now = datetime.now()
        dt = now.strftime("%d/%m/%Y %H:%M:%S")
        return {
            "success": True,
            "msg": "data saved in database successfully",
            "date": dt,
        }
    except ValidationError as ve:
      return ve.messages, 400

if __name__ == "__main__":
  app.run(debug=True)
