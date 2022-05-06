#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 13, TXPin = 15;
static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

float longitud = 0.0;
float latitud = 0.0;

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
//  Serial.println(F("DeviceExample.ino"));
//  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
//  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
//  Serial.println(F("by Mikal Hart"));
//  Serial.println();
}
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
}
void displayInfo()
{
  Serial.print(F("Location: ")); 

  Serial.print(gps.location.lat(), 6);
  longitud = gps.location.lat(), 6;
  Serial.print(F(","));
  Serial.print(gps.location.lng(), 6);
  latitud = gps.location.lng(), 6;
  Serial.println("");
  SerializeComplex();
  
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
//  Serial.print(F("  Date/Time: "));
//  if (gps.date.isValid())
//  {
//    Serial.print(gps.date.month());
//    Serial.print(F("/"));
//    Serial.print(gps.date.day());
//    Serial.print(F("/"));
//    Serial.print(gps.date.year());
//  }
//  else
//  {
//    Serial.print(F("INVALID"));
//  }
//  Serial.print(F(" "));
//  if (gps.time.isValid())
//  {
//    if (gps.time.hour() < 10) Serial.print(F("0"));
//    Serial.print(gps.time.hour());
//    Serial.print(F(":"));
//    if (gps.time.minute() < 10) Serial.print(F("0"));
//    Serial.print(gps.time.minute());
//    Serial.print(F(":"));
//    if (gps.time.second() < 10) Serial.print(F("0"));
//    Serial.print(gps.time.second());
//    Serial.print(F("."));
//    if (gps.time.centisecond() < 10) Serial.print(F("0"));
//    Serial.print(gps.time.centisecond());
//  }
//  else
//  {
//    Serial.print(F("INVALID"));
//  }
  Serial.println();
  delay(2000);
}


void SerializeComplex()
{
    Serial.println(longitud);
    Serial.println(latitud);
    String json;
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
