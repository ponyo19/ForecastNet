#include <NTPClient.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// Setup WiFi connection
const char* ssid = "aalto open"; // CHANGE THIS!
const char* password = "";  // CHANGE THIS!

// Setup sensor connection
Adafruit_BMP280 bmp; // I2C

// Retrieve date and time
WiFiUDP ntpUDP;
int timeZone = 2; // CHANGE THIS! Set timezone in GMT time, i.e: timeZone = 2 for GMT +2
NTPClient timeClient(ntpUDP, timeZone * 3600); // Setup an UDP Client to retrieve date and 
String formattedDate;
String date;
String timestamp;

unsigned long delayTime = 10000;

void setup() {
  Serial.begin(115200);

  initWiFi(); // Connect to WiFi
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

void initSensor() {
  Serial.println(F("BME280 test"));

  bool status;

  status = bmp.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
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