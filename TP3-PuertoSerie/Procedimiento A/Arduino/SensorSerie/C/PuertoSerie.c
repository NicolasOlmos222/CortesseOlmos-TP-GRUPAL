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

while(TRUE){
typedef struct{
    unsigned long tiempo;
    uint16_t sensor;
    char Lsensor;
}temperatura, humedad;

union temperatura{
    temperatura dato;
    byte t[sizeof(temperatura)];
}medicion;

union humedad{
    temperatura dato;
    byte h[sizeof(humedad)];
}medicion;

datosRecibidos = temperatura, humedad;
String datosRecibidos;

for(unsigned long long i=0; i<sizeof(temperatura); i++){
  if(datosRecibidos == "E")
    {
      printf("", medicion.t);
    }
    else if (datosRecibidos == "A")
    {
      printf("", medicion.h);
    }

  }
}
}