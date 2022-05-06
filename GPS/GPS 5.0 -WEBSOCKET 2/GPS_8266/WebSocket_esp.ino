void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  Serial.println("///////// FUNCION /////////");
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED: {
      Serial.printf("[WSc] Connected to url: %s\n", payload);

      // send message to server when Connected
      webSocket.sendTXT("Connected");
    }
      break;
    case WStype_TEXT:
      if(String((char *)payload) == ""){
        return;
      }
      Serial.printf("[WSc] get text: %s\n", payload);

      // send message to server
       webSocket.sendTXT("CONFIRMADO");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
  }

}
