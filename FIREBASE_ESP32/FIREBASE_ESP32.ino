#include "DHTesp.h"
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include <time.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <WiFiUdp.h>



#define BMP_SDA 21
#define BMP_SCL 22
#define pinDHT 15

#define trigPin 16
#define echoPin 4

long counter = 0;


Adafruit_BMP085 bmp;
DHTesp dht;

#define FIREBASE_HOST "https://integrative-project-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "ZeGDjdXsUgjbXtduXkGAEPHYobZN3qo09YMnpbce"
#define WIFI_SSID "miguee."
#define WIFI_PASSWORD "sniffer2"


  
void setup() {
  
  Serial.begin(9600);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  dht.setup(pinDHT, DHTesp::DHT11);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
 if (!bmp.begin()) {
    Serial.println("No se pudo encontrar el BMP180. Verifique las conexiones.");
    while (1);
  }

   // Configurar la zona horaria
  configTime(-6 * 3600, 0, "0.mx.pool.ntp.org");

  // Esperar a que se sincronice el tiempo
  while (!time(nullptr)) {
    Serial.println("Esperando a que se sincronice el tiempo...");
  }
 
}


void loop() {

  FirebaseData firebaseData;
  FirebaseJson json;

  String path = "/esp32";
  String user = "digitales";
  String addresses = "sensor";


  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  // ******************** SENSOR DHT11 *********************************

  TempAndHumidity data = dht.getTempAndHumidity();
  Serial.println("Temperatura: " + String(data.temperature, 2) + "°C");
  Serial.println("Humedad: " + String(data.humidity, 1) + "%");
  Serial.println("---");



  
  // ******************** SENSOR HC-SR04 *********************************
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

  // ******************** SENSOR BMP180 *********************************
  Serial.println("---");
  Serial.print("Presión: ");
  Serial.print(bmp.readPressure());
  Serial.println(" hPa");
  Serial.print("Altitud: ");
  Serial.print(bmp.readAltitude());
  Serial.println("m");
  Serial.println("---");


  // *****************************************************

   time_t nown = time(nullptr);

  // Imprimir la fecha y hora actual en el monitor serie
  Serial.println(ctime(&nown));

    // *****************************************************

  long now = millis();

    //=============================================================================================
    String Temperatura = String(data.temperature, 2);
    String Humidity = String(data.humidity, 1);
    String Distancia = String(d);
    String Presion = String(bmp.readPressure());
    String Altitud = String(bmp.readAltitude());
    String Hora = String(ctime(&nown));
    counter ++;
    json.clear().add("Id", counter);
          json.add("Temperatura", Temperatura);
          json.add("Humedad", Humidity);
          json.add("Distancia", Distancia);
          json.add("Presion", Presion);
          json.add("Altitud", Altitud);
          json.add("Hora", Hora);
 ///////////////////////////////
  //ESTO SE PUEDE REEMPLAZAR O DEJAR; SOLO ES PARA VER SI SE HA ENVIADO A LA BASE EN EL MONITOR DEL IDE ARDUINO
  if (Firebase.pushJSON(firebaseData, path + "/" + user + "/" + addresses, json)) {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.print("PUSH NAME: ");
    Serial.println(firebaseData.pushName());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
  delay(100);
                     
}
