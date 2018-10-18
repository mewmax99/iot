/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "DHT.h"
#define DHTPIN 14 // what digital pin we're connected to D5
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
ESP8266WiFiMulti WiFiMulti;

void setup() {
    Serial.begin(115200);
    Serial.println("DHT11 test!");
    dht.begin();
    delay(10);

    // We start by connecting to a WiFi network
    WiFiMulti.addAP("S7 edge", "mmmmmmmmm");

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}


void loop() {
    const uint16_t port = 80;
    const char * host = "192.168.1.1"; // ip or dns

    
    
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }

    // This will send the request to the server
    client.print("Send this data to server");
    
    delay(2000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
    return;
    }
    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);
    
    //String line = client.readStringUntil("Humidity: "+h+" %\t"+"Temperature: "+t+" *C "+f+" *F\t"+"Heat index: "+hic+" *C "+hif+" *F");
    Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" *C ");
Serial.print(f);
Serial.print(" *F\t");
Serial.print("Heat index: ");
Serial.print(hic);
Serial.print(" *C ");
Serial.print(hif);
Serial.println(" *F");
    /*client.print("Humidity: ");
    client.print(h);
    client.print(" %\t");
    client.print("Temperature: ");
    client.print(t);
    client.print(" *C ");
    client.print(f);
    client.print(" *F\t");
    client.print("Heat index: ");
    client.print(hic);
    client.print(" *C ");
    client.print(hif);
    client.println(" *F");*/

    
    /*Serial.println("closing connection");
    client.stop();
    
    Serial.println("wait 5 sec...");
    delay(5000);*/
}
