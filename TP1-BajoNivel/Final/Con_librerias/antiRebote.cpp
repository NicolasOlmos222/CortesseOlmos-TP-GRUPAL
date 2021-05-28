#include "antiRebote.h"

int estado_anteriorb;                                               //Estado real del boton sin rebotes
int estado_botonb;

unsigned long lastDebounceTime = 0;                                // ultimo momento que el pin ha cambiado
unsigned long debounceDelay = 50;                                  // tiempo de rebote, aumentar si hay rebotes

bool ciclo;

void pulsador_config (){
  //Serial.begin(9600);
  pinMode(pulsaPIN,INPUT);
  estado_anteriorb = digitalRead(pulsaPIN);                                               //Estado real del boton sin rebotes
  estado_botonb = estado_anteriorb;
}

bool pulsador_cicloA (){
  //Serial.println(PINA & (1 <<PA7));
  bool sensorValb = digitalRead(pulsaPIN);
  //Serial.println(sensorValb);
  if (sensorValb != estado_anteriorb) {
    lastDebounceTime = millis();                                    //momento en que detecto un cambio de estado del boton
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    //Cuando ha pasado el tiempo con una señal estable
    if (sensorValb != estado_botonb) {
      estado_botonb = sensorValb;
      if (estado_botonb == HIGH) {                                   //Detecto flanco ascendente, poner LOW para detectar flanco descendente
        ciclo =! ciclo;
        //Serial.println(ciclo);
        return (ciclo);
        }
      }
    }
    estado_anteriorb = sensorValb;                                      //Sin esto no funciona, actualizo para el siguente loop 
}
