#include "DHTesp.h"
#define pinDHT 21
DHTesp dht;

void setup() {
  Serial.begin(9600);
  dht.setup(pinDHT, DHTesp::DHT11);
}
void loop() {
  TempAndHumidity data = dht.getTempAndHumidity();
  Serial.println("Temperatura: " + String(data.temperature, 2) + "°C");
  Serial.println("Humedad: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  delay(1000);
}
