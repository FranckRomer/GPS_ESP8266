#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

const char* ssid     = "TP-Link_6C72";
const char* password = "16823099";
char path[] = "/";
char host[] = "192.168.0.101";

/*
 *    VAR GPS  
*/
static const int RXPin = 13, TXPin = 15;
static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

  
WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections
WiFiClient client;

/*
 *  VARIABLES  GLOBALES 
*/
double longitud = 0.0;
double latitud = 0.0;
String json = "";


/*
 **************************************** 
 *          SETUP 
 *****************************************
*/
void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println();
  
  setup_wifi();
  reconect_websocket();
  
}

/*
 **************************************** 
 *          LOOP 
 *****************************************
*/
void loop() {

  while (ss.available() > 0){
    if (gps.encode(ss.read())){
      displayInfo();
      delay(50);
      //send_msm_websocket();
      }
  }
      
  if (millis() > 3000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    //while(true);
  }
  // ENVIAR MENSAJE POR WEBSOCKET
  //send_msm_websocket();
  // wait to fully let the client disconnect
  //delay(3000); 
}
