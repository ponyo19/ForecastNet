#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <Wire.h>

#define SEALEVELPRESSURE_HPA (1013.25)

const char* ssid = "aalto open";
const char* password = "";


Adafruit_BMP280 bmp; // I2C

unsigned long delayTime = 10000;

void setup() {
  Serial.begin(115200);

  initSensor(); // Setup BMP280 sensor
  initWiFi(); // Connect to WiFi
}


void loop() { 
  printValues();
  delay(delayTime);
}

void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure() / 100.0F);
  Serial.println(" hPa");

  // For BME280 sensor
  // Convert temperature to Fahrenheit
  /*Serial.print("Temperature = ");
  Serial.print(1.8 * bme.readTemperature() + 32);
  Serial.println(" *F");*/

  // Serial.print("Approx. Altitude = ");
  // Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  // Serial.println(" m");

  Serial.println();
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print(("Connecting to WiFi ..."));
  while (WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(1000);
  }
  Serial.println("\nWiFi connected!");
  Serial.println("Local IPv4:");
  Serial.println(WiFi.localIP());
}

void initSensor() {
  Serial.println(F("BME280 test"));

  bool status;

  status = bmp.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}