#include <NTPClient.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// CHANGE PARAMETERS!
// Setup WiFi connection
const char* ssid = ""; // CHANGE THIS!
const char* password = "";  // CHANGE THIS!

// Setup MQTT connection
const char* mqtt_server = ""; // CHANGE THIS!
const char* mqtt_username = ""; // CHANGE THIS!
const char* mqtt_password = ""; // CHANGE THIS!
const char* clientID = "Home"; // CHANGE THIS!
const char* temperature_topic = "temperature";

// Set timezone in GMT time, i.e: timeZone = 2 for GMT +2
int timeZone = 2; // CHANGE THIS! 

// Setup I2C sensor connection
Adafruit_BMP280 bmp; 

// Initialise WiFi and MQTT client object
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient);

// Initialise time client object
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, timeZone * 3600); // Setup an UDP Client to retrieve date and time
String formattedDate;
String date;
String timestamp;

unsigned long delayTime = 10000;

void setup() {
  Serial.begin(115200);
  initWiFi(); // Connect to WiFi
  initMQTT(); // Connect to MQTT broker
  initSensor(); // Setup sensor
}


void loop() { 
  printValues();
  delay(delayTime);
}

void printValues() {
  getAndFormatTime();
  Serial.print("Date: ");
  Serial.println(date);
  Serial.print("Time: ");
  Serial.println(timestamp);
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

void initMQTT() {
  // Connect to MQTT Broker
    while (!client.connected()) {
    Serial.print("Connecting to MQTT broker ...");
    if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
      Serial.println("\nMQTT broker connected!");
    } 
    else {
      Serial.print("\nMQTT broker not connected: ");
      Serial.print(client.state());
      Serial.println("Retrying.");
      delay(5000);
    }
  }
}

void initSensor() {
  Serial.println(F("BMP280 test"));

  bool status;

  status = bmp.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 5000;

  Serial.println();

  timeClient.begin(); // Start timeClient
}

void getAndFormatTime() {
  while(!timeClient.update()){
    timeClient.forceUpdate();
  }
  formattedDate = timeClient.getFormattedDate();

  int splitTime = formattedDate.indexOf("T");
  date = formattedDate.substring(0, splitTime);
  timestamp = formattedDate.substring(splitTime + 1, formattedDate.length() - 1);
}