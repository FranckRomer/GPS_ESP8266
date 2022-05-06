#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <WebSocketClient.h>

const char* ssid     = "TP-Link_6C72";
const char* password = "16823099";
char path[] = "/";
char host[] = "192.168.0.102";



WebSocketClient webSocketClient;
// Use WiFiClient class to create TCP connections
WiFiClient client;

static const int RXPin = 13, TXPin = 15;
static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

float longitud = 0.0;
float latitud = 0.0;
String json;

/*
 *******************************************************************
 *                      SETUP
 ********************************************************************
*/

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to the websocket server
  if (client.connect("192.168.0.102", 81)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
    while(1) {
      // Hang on failure
    }
  }

  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
    
  }
}

/*
 *******************************************************************
 *                      LOOP
 *******************************************************************
*/
void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
  if (millis() > 3000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }


  /////////////////////////

  String data;

  if (client.connected()) {
    
//    webSocketClient.getData(data);
//    if (data.length() > 0) {
//      Serial.print("Received data: ");
//      Serial.println(data);
//    }
    
    webSocketClient.sendData(json);
    
  } else {
        Serial.println("Client disconnected.");
//        //webSocketClient.reconnect();
//        webSocketClient.path = path;
//      webSocketClient.host = host;
//      if (webSocketClient.handshake(client)) {
//        Serial.println("Handshake successful");
//      } else {
//        Serial.println("Handshake failed.");
//        
//      }
  }
  
  // wait to fully let the client disconnect
  delay(3000);
  
}
void displayInfo()
{
  Serial.print(F("Location: ")); 

  
  
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    longitud = gps.location.lat(), 6;
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    latitud = gps.location.lng(), 6;
    Serial.println("");
    SerializeComplex();
    
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
  delay(2000);
}


void SerializeComplex()
{
    Serial.println(longitud);
    Serial.println(latitud);
    //String json;
    StaticJsonDocument<32768> doc;    //fichero vacio que pasara a ser array
    doc["id_gps"] = "gps01";      //prioridad clave/valor con doc (pasa a sere un objeto)
    doc["latitud"] = longitud;
    doc["longitud"] = latitud;
    
    serializeJson(doc, json);
    Serial.println(json);
}


//void DeserializeComplex()
//{
//    String json = "{\"text\":\"myText\",\"id\":10,\"status\":true,\"value\":3.14,\"nestedObject\":{\"key\":40,\"description\":\"myDescription\",\"active\":true,\"qty\":1.414},\"nestedArray\":[\"B\",45,2.1728,true]}";
//
//    StaticJsonDocument<300> doc;      //para indicar la memoria disponible del json
//    DeserializationError error = deserializeJson(doc, json);
//    if (error) { return; }
//
//    String text = doc["text"];
//    int id = doc["id"];
//    bool stat = doc["status"];
//    float value = doc["value"];
//
//    Serial.println(text);
//    Serial.println(id);
//    Serial.println(stat);
//    Serial.println(value);
//
//    
//}
