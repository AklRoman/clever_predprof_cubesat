#include <ESP8266WiFi.h>
#include <HTTPClient.h>
const char ssid = 
const char password =
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.println("Подключение к WI-FI");
  }
  Serial.println("Подключени к WI-FI");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin("http://api.thingspeak.com/update?api_key=YOUR_API_KEY&field1=0");
    int httpCode = http.GET();
    String payload = http.getString(); 
    Serial.println(httpCode);
    Serial.println(payload); 
    http.end();
  } else {
    Serial.println("Ошибка подключения к WI-FI");
  }
  delay(45000);
}
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

Adafruit_BME280 bme; // I2C

void setup() {
  Serial.begin(115200);
  Serial.println(F("BME280 test"));
  SPI.begin(BME_SCK, BME_MISO, BME_MOSI, BME_CS);
  bool status;
  status = bme.begin();  
  if (!status) {
    Serial.println("Не удалось найти датчик");
    while (1);
  }

  Serial.println("-- Default Test --");
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());

  Serial.println(" *C");
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  Serial.println();
}

void loop() {
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float humidity = bme.readHumidity();

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(5000);
}
#include <SX1278.h>
#include <SPI.h>

// SX1278 pins
#define NSS 10
#define NRESET 9
#define DIO0 3

  byte packetSize = 255;

  void setup() {

    Serial.begin(115200); 

    SPI.begin(); 

    SX1278.init(NSS, NRESET, DIO0); 

    SX1278.setFrequency(868); 

    SX1278.setMode(MODE_LORA);

    SX1278.setPower(17) 

    SX1278.setBandwidth(BW_125KHZ); 

    SX1278.setSpreadingFactor(SF7); 

    SX1278.setCodingRate(CR4_8); 

    SX1278.setSyncWord(0x12);

    SX1278.setPacketSize(packetSize);
    Serial.println("SX1278 is ready!");
  }
  void loop() { 

    if (Serial.available()) {  

      byte data[packetSize];  

      int i = 0;  

      while (Serial.available() && i < packetSize) {  

        data[i] = Serial.read();  

        i++;  

      }  
      if (SX1278.sendPacket(data, packetSize)) {  

        Serial.println("Packet sent successfully!");  

      } else {  
        Serial.println("Error sending packet!");  
      }  
    }  
  }
#include <Wire.h>
#define CHRG_EN 5
#define CHRG_STAT 6

void setup() {
  Serial.begin(9600);
  pinMode(CHRG_EN, OUTPUT);
  pinMode(CHRG_STAT, INPUT);
  digitalWrite(CHRG_EN, HIGH);
}

void loop() {
  int status = digitalRead(CHRG_STAT);

  if (status == HIGH) {
    Serial.println("Подзарядка 11.1V 1100mAh Li-Po battery");
  } else {
    Serial.println("Подзарядка окончена");
  }

  delay(10000);
}
