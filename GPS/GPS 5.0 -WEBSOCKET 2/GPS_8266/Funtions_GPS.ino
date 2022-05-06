/*
 ************************************************ 
 *        displayInfo
 ************************************************
*/

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
    Serial.println("");
    longitud = 0.0;
    latitud  = 0.0;
    SerializeComplex();
  }
  Serial.println();
  delay(2000);
}
