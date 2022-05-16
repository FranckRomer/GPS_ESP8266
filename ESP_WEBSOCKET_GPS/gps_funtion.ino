void displayInfo()
{
  Serial.print(F("Location: ")); 

  
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    latitud = gps.location.lat(), 6;
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    longitud = gps.location.lng(), 6;
    Serial.println("");
    SerializeComplex();
    send_msm_websocket();
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
  delay(1000);
}
