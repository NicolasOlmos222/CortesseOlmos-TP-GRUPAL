#include "antiRebote.h"                                                                                           //Libreria local

unsigned long tiempo;
unsigned long tiempoActual;

int desplazamientoC = 0b00000000;
int desplazamientoB = 0b11111101;
int contador = 0;

bool primerLoop = 0;

//Letras:
int A[8] = {0b11100111, 0b11000011, 0b10011001, 0b00111100, 0b00000000, 0b00000000, 0b00111100, 0b00111100};
int N[8] = {0b00011100, 0b00001100, 0b00001100, 0b00100100, 0b00100100, 0b00110000, 0b00110000, 0b00111000};

void setup() {
  tiempo = millis();
  DDRC = 0b11111111;                                                                                                //Pines de salida columnas
  DDRB = 0b11111111;                                                                                                //Pines de salida Filas
  pulsador_config();                                                                                                //Funcion de libreria local para setup
  Serial.begin(9600);
  Serial.print("Tiempo setup: "); Serial.print(micros()); Serial.println(" micros");
}

void loop() {
  //prueba_leds();
  PORTC = desplazamientoC;
  PORTB = desplazamientoB;
  
  if(pulsador_cicloA() == 1){                                                                                       //Si el ciclo del pulsador esta en 1, imprime la N, en lo contrario A
    desplazamientoC = desplazamientoC << 1;
    desplazamientoB = N[contador];
    contador ++;
  }else{
    desplazamientoC = desplazamientoC << 1;
    desplazamientoB = A[contador];
    contador ++;
  }
  
  if (desplazamientoC == 0b00000000){                                                                               //Reinicia Columna si termino su ciclo.
    desplazamientoC = 0b00000001;
  }
  if(contador == 8){                                                                                                //Reinicia Fila si termino su ciclo.
    contador = 0;
  }

  if(primerLoop == 0){
    Serial.print("Tiempo hasta fin de loop: "); Serial.print(micros()); Serial.println(" micros");
    primerLoop = 1;
  }
}

void prueba_leds(){
  PORTC = desplazamientoC;
  PORTB = desplazamientoB;
  
  if (((tiempoActual = millis()) - tiempo) >= 100){                                                                 //Cambia de led cada 100 millis
    tiempo = tiempoActual;
    if (desplazamientoC == 0b00000000){                                       
      desplazamientoC = 0b00000001;
      if(contador == 7){
        desplazamientoC = 0b00000001;
        desplazamientoB = 0b11111110;
        contador = 0;
      }else desplazamientoB = desplazamientoB << 1 | desplazamientoB >> 7; contador++;
    }else desplazamientoC = desplazamientoC << 1;
  }
}
