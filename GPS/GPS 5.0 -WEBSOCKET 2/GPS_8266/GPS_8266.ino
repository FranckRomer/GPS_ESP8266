#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <Hash.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;


/*
 * GPS
*/
static const int RXPin = 13, TXPin = 15;
static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


/*
 *  VARIABLES
 */
float longitud = 0.0;
float latitud = 0.0;
String json = "";


/*
 ******************************************************
 *            SETUP
 ****************************************************** 
*/
void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

  //Serial.setDebugOutput(true);
  Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFiMulti.addAP("TP-Link_6C72", "16823099");

  //WiFi.disconnect();
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  // server address, port and URL
  webSocket.begin("192.168.0.102", 81, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // use HTTP Basic Authorization this is optional remove if not needed
  //webSocket.setAuthorization("user", "Password");

  // try ever 5000 again if connection has failed
  //webSocket.setReconnectInterval(5000);

}

/*
 ******************************************************
 *            LOOP
 ****************************************************** 
*/
void loop()
{

  // This sketch displays information every time a new sentence is correctly encoded.
  if (ss.available() > 0)
    if (gps.encode(ss.read()))
      Serial.println("gps");
      displayInfo();
      
  if (millis() > 3000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));  
  }

  webSocket.loop();
 
}
