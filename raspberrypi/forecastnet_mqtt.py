import paho.mqtt.client as mqtt
import json
import mysql.connector

mqtt_broker = "localhost"
mqtt_port = 1883
mqtt_topic = "readings"
mqtt_username = ""  # CHANGE THIS
mqtt_password = ""  # CHANGE THIS

mydb = mysql.connector.connect(
    host="localhost",
    user="root",  # Default mysql username
    password="",  # CHANGE TO YOUR DATABASE PASSWORD
    database="forecastnet",
)


def on_connect(client, userdata, flags, rc, properties):
    print("Connected with result code: " + str(rc))
    client.subscribe(mqtt_topic)


def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))
    payload = json.load(msg.payload.decode("utf-8"))
    cursor = mydb.cursor()
    temperature = payload["temperature"]
    date = payload["date"]
    time = payload["time"]
    location = payload["location"]

    sql = "INSERT INTO sensorData (location, temperature, date, time) VALUES (%s, %s, %s, %s)"
    val = (location, temperature, date, time)
    cursor.execute(sql, val)


mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.on_connect = on_connect
mqttc.on_message = on_message

mqttc.connect(mqtt_broker, mqtt_port, 60)

mqttc.loop_forever()
