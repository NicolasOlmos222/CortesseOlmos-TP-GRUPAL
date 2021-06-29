#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "rs232.h"

#define LONG_BUFFER 4096

int main(){

int puertoCOM = 4;
int baudios = 9600;
char modo[] = {'8', 'n', '1', 0};

unsigned char bufferReception[LONG_BUFFER];
int cantidadBytes;

if(RS232_OpenComport(puertoCOM, baudios, modo, 0)){
    printf("No se puedo abrir el puerto COM\n");
    return 0;
}
(
while(TRUE){

typedef struct {
    unsigned long tiempo;
    uint16_t sensor;
    char Lsensor;
}temperatura, humedad, potenciometro1, potenciometro2;

union informacion{
    informacion dato;
    byte i[sizeof(temperatura, humedad, potenciometro1, potenciometro2)];
}medicion;

  printf("Ingrese la inicial del sensor deseado (P, R, T, H): ");
  scanf("%c", &inicial);

  if(!strcmp(&inicial, "T")){
    rs232_SendByte(puertoCOM, 'T');
  }
  else if(!strcmp(&inicial, "H")){
    rs232_SendByte(puertoCOM, 'H');
  }
   else if(!strcmp(&inicial, "P")){
    rs232_SendByte(puertoCOM, 'P');
  }
   else if(!strcmp(&inicial, "R")){
    rs232_SendByte(puertoCOM, 'R');
  }

if(cantidadBytes = RS232_PollComport(puertoCom, medicion.i, sizeof(temperatura, humedad, potenciometro1, potenciometro2))){
  printf("%c\n", medicion.i);
 }
}