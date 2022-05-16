/*
 * send_msm_websocket
*/

void send_msm_websocket(){
  String data;
  if (client.connected()) {
    // ENVIO DE DATOS
    webSocketClient.sendData(json);
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
}
