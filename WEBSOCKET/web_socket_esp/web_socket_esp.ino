#include <ESP8266WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "TP-Link_6C72";
const char* password = "16823099";
const char* IP_websockt = "192.168.0.101";
char path[] = "/";
char host[] = "192.168.0.101";
  
WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections
WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println();
  
  setup_wifi();
  reconect_websocket();
  
}


void loop() {
  String data;

  if (client.connected()) {
    // ENVIO DE DATOS
    webSocketClient.sendData("HOLAAAAAAAAAA");
    // RECIBO DE DATOS
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
    
  } else {
    Serial.println("Client disconnected.");
    reconect_websocket();
  }
  
  // wait to fully let the client disconnect
  delay(3000);
  
}
