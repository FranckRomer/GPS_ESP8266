#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

void SerializeComplex()
{
    String json;
    StaticJsonDocument<300> doc;    //fichero vacio que pasara a ser array
    doc["id_gps"] = "gps01";      //prioridad clave/valor con doc (pasa a sere un objeto)
    doc["latitud"] = "+65+65+65";
    doc["longitud"] = "545451";
 

    
    serializeJson(doc, json);
    Serial.println(json);
}

void DeserializeComplex()
{
    String json = "{\"text\":\"myText\",\"id\":10,\"status\":true,\"value\":3.14,\"nestedObject\":{\"key\":40,\"description\":\"myDescription\",\"active\":true,\"qty\":1.414},\"nestedArray\":[\"B\",45,2.1728,true]}";

    StaticJsonDocument<300> doc;      //para indicar la memoria disponible del json
    DeserializationError error = deserializeJson(doc, json);
    if (error) { return; }

    String text = doc["text"];
    int id = doc["id"];
    bool stat = doc["status"];
    float value = doc["value"];

    Serial.println(text);
    Serial.println(id);
    Serial.println(stat);
    Serial.println(value);

    int key = doc["nestedObject"]["key"];
    String description = doc["nestedObject"]["description"];
    bool active = doc["nestedObject"]["active"];
    float qty = doc["nestedObject"]["qty"];

    Serial.println(key);
    Serial.println(description);
    Serial.println(active);
    Serial.println(qty);

    String item0 = doc["nestedArray"][0];
    int item1 = doc["nestedArray"][1];
    float item2 = doc["nestedArray"][2];
    bool item3 = doc["nestedArray"][3];

    Serial.println(item0);
    Serial.println(item1);
    Serial.println(item2);
    Serial.println(item3);
}

void setup()
{
    Serial.begin(115200);

    Serial.println("===== Complex Example =====");
    Serial.println("-- Serialize --");
    SerializeComplex();
//    Serial.println();
//    Serial.println("-- Deserialize --");
//    DeserializeComplex();
//    Serial.println();
}

void loop()
{
}
