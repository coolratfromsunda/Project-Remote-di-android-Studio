
#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Setting MAC Address

#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


float humidityData;
float temperatureData;


char server[] = "20.30.40.39";
IPAddress ip(20,30,40,33); 
EthernetClient client; 

/* Setup for Ethernet and RFID */

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (Ethernet.begin(mac) == 0) {
  Serial.println("Failed to configure Ethernet using DHCP");
  Ethernet.begin(mac, ip);
  }
  delay(10);
}
//------------------------------------------------------------------------------


/* Infinite Loop */
void loop(){
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(); 
  Sending_To_phpmyadmindatabase(); 
  delay(60); // interval
}


  void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /testcode/dht.php");
    client.print("GET /testcode/dht.php");     //YOUR URL
    client.print("?temperature=");
    Serial.println("?temperature=");
    client.print(temperatureData);
    Serial.println(temperatureData);
    client.print("&humidity=");
    Serial.println("&humidity=");
    client.print(humidityData);
    Serial.println(humidityData);
    
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 20.30.40.39");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
