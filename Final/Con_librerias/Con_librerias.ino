#include "antiRebote.h"

int columnaPIN[8] = {53, 52, 51, 50, 10, 11, 12, 13};
int filaPIN[8] = {37, 36, 35, 34, 33, 32, 31, 30};

bool primerLoop = 0;

//Letras:
int A[8][8] = {
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 0, 0},
{0, 1, 1, 0, 0, 1, 1, 0}, 
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1}
};

int N[8][8] = {
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 1, 1, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 0, 0, 1, 1},
{1, 1, 0, 1, 1, 0, 1, 1},
{1, 1, 0, 0, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1}
};

void setup() {
  for(int i = 0; i <= 8; i++){
    pinMode(columnaPIN[i], OUTPUT);
    pinMode(filaPIN[i], OUTPUT);
  }
  pulsador_config();
  Serial.begin(9600);
  Serial.print("Tiempo setup: "); Serial.print(micros()); Serial.println(" micros");
  limpieza();
}

void loop() {
  if(pulsador_cicloA() == 1){
    for(int columna = 0; columna <= 7; columna++){
      digitalWrite(columnaPIN[columna], LOW);
      for(int fila = 0; fila <= 7; fila++){
        digitalWrite(filaPIN[fila], A[columna][fila]);
      }
      digitalWrite(columnaPIN[columna], HIGH);
      limpieza();
    }
  }else{
    for(int columna = 0; columna <= 7; columna++){
      digitalWrite(columnaPIN[columna], LOW);
      for(int fila = 0; fila <= 7; fila++){
        digitalWrite(filaPIN[fila], N[columna][fila]);
      }
      digitalWrite(columnaPIN[columna], HIGH);
      limpieza();
    }
  }
  
  
  if(primerLoop == 0){
    Serial.print("Tiempo hasta fin de loop: "); Serial.print(micros()); Serial.println(" micros");
    primerLoop = 1;
  }
}

void limpieza(){
  for(int columna = 0; columna <= 7; columna++){
    digitalWrite(columnaPIN[columna], HIGH);
    for(int fila = 0; fila <= 7; fila++){
      digitalWrite(filaPIN[fila], LOW);
    }
  }
}
