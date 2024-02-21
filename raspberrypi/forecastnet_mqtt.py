import paho.mqtt.client as mqtt

mqtt_broker = "localhost"
mqtt_port = 1883
mqtt_topic = "readings"
mqtt_username = ""  # CHANGE THIS
mqtt_password = ""  # CHANGE THIS


def on_connect(client, userdata, flags, rc):
    print("Connected with result code: " + str(rc))
    client.subscribe(mqtt_topic)


def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))


mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.on_connect = on_connect
mqttc.on_message = on_message

mqttc.connect(mqtt_broker, mqtt_port, 60)

mqttc.loop_forever()
