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
- mariadb-server
- php-mysql
- phpmyadmin
- mosquitto
- mosquitto-clients

... To be updated

