#include "AutoArduino.h"

void autoArduino(String letra){
  pinMode(PIN_LED, OUTPUT);
  
  while(!Serial.available()){
    if(datosRecibidos == letra){
      digitalWrite(LED, HIGH);
      Serial.println(letra);
    }
}
