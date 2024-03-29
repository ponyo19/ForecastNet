#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <NTPClient.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>

#define SEALEVELPRESSURE_HPA (1013.25)

#define uS_TO_S_FACTOR \
  1000000                 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 300 /* Time ESP32 will go to sleep (in seconds) */
RTC_DATA_ATTR int bootCount = 0;

// CHANGE PARAMETERS!
// Setup WiFi connection
const char* ssid = "";      // CHANGE THIS!
const char* password = "";  // CHANGE THIS!

// Setup MQTT connection
const char* mqtt_server = "";    // CHANGE THIS!
const char* mqtt_username = "";  // CHANGE THIS!
const char* mqtt_password = "";  // CHANGE THIS!
const char* clientID = "Home";   // CHANGE THIS!
const char* readings_topic = "readings";
char data[80];

// Set timezone in GMT time, i.e: timeZone = 2 for GMT +2
int timeZone = 2;  // CHANGE THIS!

// Setup I2C sensor connection
Adafruit_BMP280 bmp;

// Initialise WiFi and MQTT client object
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient);

// Initialise time client object
WiFiUDP ntpUDP;
NTPClient timeClient(
    ntpUDP, timeZone * 3600);  // Setup an UDP Client to retrieve date and time
String formattedDate;
String date;
String timestamp;

// Delay time between transmissions
unsigned long delayTime = 60000;

void setup() {
  Serial.begin(115200);
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  initWiFi();    // Connect to WiFi
  initSensor();  // Setup sensor
  connect_MQTT();
  Serial.setTimeout(2000);
  send_MQTT();
  client.disconnect();

  // Put the ESP32 to sleep
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                 " Seconds");
  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush();
  esp_deep_sleep_start();
}

void loop() {}

void send_MQTT() {
  getAndFormatTime();
  Serial.print("Date: ");
  Serial.println(date);
  Serial.print("Time: ");
  Serial.println(timestamp);
  Serial.print("Temperature = ");
  float temperature = bmp.readTemperature();
  Serial.print(temperature);
  Serial.println(" *C");

  String readings = "{\"temperature\":\"" + String(temperature) +
                    "\", \"date\":\"" + date + "\", \"time\":\"" + timestamp +
                    "\", \"location\":\"" + clientID + "\"}";
  readings.toCharArray(data, (readings.length() + 1));

  if (client.publish(readings_topic, data)) {
    Serial.println("Readings sent!");
  } else {
    Serial.println("Readings failed to send!");
  }

  Serial.println();
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print(("Connecting to WiFi ..."));
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("\nWiFi connected!");
  Serial.println("Local IPv4:");
  Serial.println(WiFi.localIP());
}

void connect_MQTT() {
  // Connect to MQTT Broker
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker ...");
    if (client.connect(clientID, mqtt_username, mqtt_password)) {
      Serial.println("MQTT broker connected!");
    } else {
      Serial.print("MQTT broker not connected: ");
      Serial.println(client.state());
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
    while (1)
      ;
  }

  Serial.println("-- Default Test --");
  delayTime = 5000;

  Serial.println();

  timeClient.begin();  // Start timeClient
}

void getAndFormatTime() {
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  formattedDate = timeClient.getFormattedDate();

  int splitTime = formattedDate.indexOf("T");
  date = formattedDate.substring(0, splitTime);
  timestamp =
      formattedDate.substring(splitTime + 1, formattedDate.length() - 1);
}