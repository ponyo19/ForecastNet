# ForecastNet: A ML-enhanced weather station network

This project is a IoT weather station network that displays past data and simplified forecasts using Linear Regression on a website.

## Overview
- A station in the network consists of a ESP32 and a BME280 sensor.
- The Raspberry Pi works as an always-on server.
- MQTT is used for communication between the stations and the server.
- LAMP stack manages and stores data in a MySQL database and builds web interface for displaying data.
- Prediction is performed using a Python script that parse data from MySQL for model training and prediction with scikit-learn.

## Preparation
### Parts required
- A Raspberry Pi board.
- A ESP32 and a BME280 sensor for each station.

### Required libraries

For Arduino IDE:
- esp32 by Espressif Systems
- Adafruit Unified Sensor
- Adafruit BME280

... To be updated

