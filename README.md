# ForecastNet: A ML-enhanced weather station network

This project is a IoT weather station network that displays past data and forecasts using Linear Regression on a website.

## Overview
- A station in the network consists of an ESP32 and a BMP280 sensor.
- The Raspberry Pi works as an always-on server.
- MQTT is used for communication between the stations and the server.
- LAMP stack (Linux/ Apache/ MySQL/ PHP) manages and stores data in a MySQL database and builds web interface for displaying data.
- Prediction is performed using a Python script that parses data from MySQL for model training and prediction with scikit-learn.

## Preparation
### Parts required
- A Raspberry Pi board.
- An ESP32 and a BMP280 sensor for each station.

### Required libraries
For ESP32 Arduino IDE:
- esp32 by Espressif Systems
- Adafruit Unified Sensor
- Adafruit BMP280
- NPTClient by Taranais
- PubSubClient by Nick O'Leary

For Raspberry Pi Raspbian OS:
- apache2
- php
- python3
- mariadb-server
- php-mysql
- phpmyadmin
- mosquitto
- mosquitto-clients

## How to run this project
### On ESP32
- Setup the board following this schema
- Install all required libraries
- Load the source code at ```./esp32/esp32_sketch/esp32_sketch.ino``` to Arduino IDE
- Change WiFi and MQTT credentials
- Upload the modified code to ESP32

### On Raspberry Pi
- Install all required libraries
- Setup mosquitto MQTT broker and MySQL database following this [tutorial](https://randomnerdtutorials.com/raspberry-pi-apache-mysql-php-lamp-server/)
- EXTRA: Check if the broker port 1883 on the server is open by running ```nmap -p 1883 <broker address>``` from a computer in the local network. Open the port if closed.
- (Recommended) Create and use a Python virtual environment
- Run ```pip install -r ./raspberrypi/requirements.txt``` to install necessary Python libraries
- Modify MQTT and MySQL credentials and run ```python ./raspberrypi/forecastnet_server.py``` to start the server for uploading sensor data. 
- Data sent from ESP32 can now be browsed by accessing ```<your server address>/myphpadmin``` from a browser on any computer in the local network

... To be updated

