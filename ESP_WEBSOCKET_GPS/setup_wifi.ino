/*
 *  SETUP WIFI
*/

void setup_wifi(){
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
}


void reconect_websocket(){
  // Connect to the websocket server
  Serial.println("Intentando conectar websocket");
  if (client.connect("192.168.0.101", 81)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
    
  }
  //Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
  }
}
