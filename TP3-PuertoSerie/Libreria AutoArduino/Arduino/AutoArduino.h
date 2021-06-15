/*  AutoArduino:
 *  Seleccion automatica del puerto en donde se encuentra el arduino conectado.
 *  Se debe usar la misma letra en c y arduino.
 *  Desde arduino a la funcion se la llama con: autoArduino( LETRA );
 *  Al detectar el puerto, se prende el LED
 *  Usar Serial.begin !!! <---
 */
#include <arduino.h>

#define PIN_LED 13

void autoArduino(String letra);
