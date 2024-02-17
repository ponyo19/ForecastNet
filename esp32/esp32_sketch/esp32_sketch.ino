#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SPI.h>

// Assign SPI GPIO pins
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5

#define SEALEVELPRESSURE_HPA (1013.25)


Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // Setup software SPI
// Adafruit_BME280 bme(BME_CS) // Or use hardware SPI which will use the board's default SPI GPIO pins

unsigned long delayTime;

void setup() {
  Serial.begin(9600);
  Serial.println(F("BME280 test"));

  bool status;

  status = bme.begin();  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}


void loop() { 
  printValues();
  delay(delayTime);
}

void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  // Convert temperature to Fahrenheit
  /*Serial.print("Temperature = ");
  Serial.print(1.8 * bme.readTemperature() + 32);
  Serial.println(" *F");*/
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}