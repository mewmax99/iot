#include "DHT.h"
#define DHTPIN 14 // what digital pin we're connected to D5
#define DHTTYPE DHT11 // DHT 11
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
ESP8266WiFiMulti WiFiMulti;

DHT dht(DHTPIN, DHTTYPE);
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
delay(2000);
// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
// Read temperature as Fahrenheit (isFahrenheit = true)
float f = dht.readTemperature(true);
// Check if any reads failed and exit early (to try again).
if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println("Failed to read from DHT sensor!");
 return;
}
// Compute heat index in Fahrenheit (the default)
float hif = dht.computeHeatIndex(f, h);
// Compute heat index in Celsius (isFahreheit = false)
float hic = dht.computeHeatIndex(t, h, false);


    const uint16_t port = 8000;
    const char * host = "192.168.43.87"; // ip or dns

    
    
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
    

    String h2;
    h2 = String(h);
    String t2;
    t2 = String(t);
    String f2;
    f2 = String(f);
    String hif2;
    hif2 = String(hif);
    String hic2;
    hic2 = String(hic);
    client.print("Humidity: ");
    client.print(h);
    client.print(" %\t");
    client.print("Temperature: ");
    client.print(t2);
    client.print(" *C ");
    client.print(f2);
    client.print(" *F\t");
    client.print("Heat index: ");
    client.print(hic2);
    client.print(" *C ");
    client.print(hif2);
    client.print(" *F");


    Serial.println("closing connection");
    client.stop();
    
    Serial.println("wait 5 sec...");
    delay(5000);


    Wire.begin(); 
  oled.init();                      // Initialze SSD1306 OLED display
  oled.clearDisplay();              // Clear screen
  oled.setTextXY(2,0);              // Set cursor position, start of line 0
  oled.putString("Humidity: "+h2+" %\t");
  oled.setTextXY(2,0);              // Set cursor position, start of line 1
  oled.putString("Temperature: "+t2+" *C "+f2+" *F\t");
  oled.setTextXY(2,0);              // Set cursor position, start of line 2
  oled.putString("Heat index: "+hic2+" *C "+hif2+" *F");
  delay(50000);


  

    

}