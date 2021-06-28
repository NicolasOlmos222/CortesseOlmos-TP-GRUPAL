#include "AutoArduino.h"

String dato;
bool bandera = 1;

void autoArduino(String letra){
  Serial.begin(9600);
  pinMode(PIN_LED ,OUTPUT);

  while(bandera){
    if(Serial.available()>0){
      dato = Serial.readString();
      //Serial.println(dato);

      if(dato == letra){
        digitalWrite(PIN_LED, HIGH);
        Serial.println("~~Puerto identificado~~");
        bandera = 0;
      }
    }
  }
}
