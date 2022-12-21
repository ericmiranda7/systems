#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <stdlib.h>

// GPIO where the DS18B20 is connected to
#define DS_GPIO_PIN 4

// WiFi things
const char *ssid = "23";
const char *password = "Cookies_007";

// MQTT Things
const char *mqtt_broker = "192.168.1.12";
const char *topic = "iot/temp";
const int mqtt_port = 1883;

// Wifi client
WiFiClient espClient;
PubSubClient client(espClient);

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(DS_GPIO_PIN);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();

  // connect to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi....");
  }

  Serial.println("Connected to WiFi !");

  // connect to broker
  client.setServer(mqtt_broker, mqtt_port);
  //client.setCallback(callback);
  

  while (!client.connected())
  {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());

    Serial.printf("The client %s connects to mosquitto mqtt broker\n", client_id.c_str());
    
    if (client.connect(client_id.c_str()))
    {
      Serial.println("Connected to MQTT broker");
    }
    else
    {
      Serial.print("failed with ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  char buffer[64];
  snprintf(buffer, sizeof buffer, "%f", temperatureC);
  client.publish(topic, buffer);
  Serial.println("ºC");
  delay(2000);
}
