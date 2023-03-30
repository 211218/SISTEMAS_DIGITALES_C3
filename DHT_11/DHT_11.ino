#include "DHTesp.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>


#define BMP_SDA 21
#define BMP_SCL 22
#define pinDHT 15

#define trigPin 16
#define echoPin 4

Adafruit_BMP085 bmp;
DHTesp dht;

void setup() {
  Serial.begin(9600);
  dht.setup(pinDHT, DHTesp::DHT11);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
 if (!bmp.begin()) {
    Serial.println("No se pudo encontrar el BMP180. Verifique las conexiones.");
    while (1);
  } 
}


void humedad(){
  TempAndHumidity data = dht.getTempAndHumidity();
  Serial.println("Temperatura: " + String(data.temperature, 2) + "°C");
  Serial.println("Humedad: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  delay(1000);
}

void ultrasonico(){
  long t; 
  long d; 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);        
  digitalWrite(trigPin, LOW);
  
  t = pulseIn(echoPin, HIGH); 
  d = t/59;            
  
  Serial.print("Distancia: ");
  Serial.print(d);    
  Serial.print("cm");
  Serial.println();
  Serial.println("---");
  delay(100);      
}

void barometro(){
  Serial.println("---");
  Serial.print("Presión: ");
  Serial.print(bmp.readPressure());
  Serial.println(" hPa");
  Serial.print("Altitud: ");
  Serial.print(bmp.readAltitude());
  Serial.println("m");
  Serial.println("---");
  delay(1000);
}


void loop() {
  humedad();
  ultrasonico();
  barometro();
}
