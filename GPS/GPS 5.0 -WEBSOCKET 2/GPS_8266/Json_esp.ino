void SerializeComplex()
{
    Serial.println(longitud);
    Serial.println(latitud);
    json;
    StaticJsonDocument<32768> doc;    //fichero vacio que pasara a ser array
    doc["id"] = "gps";      //prioridad clave/valor con doc (pasa a sere un objeto)
    doc["latitud"] = longitud;
    doc["longitud"] = latitud;
    
    serializeJson(doc, json);
    Serial.println(json);
    webSocket.sendTXT(json);
    json = "";
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
