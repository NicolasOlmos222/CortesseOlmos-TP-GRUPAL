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
typedef struct {
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

if(cantidadBytes = RS232_PollComport(puertoCom, medicion.t, sizeof(temperatura))){
    printf("El sensor es %c\n", medicion.temperatura.Lsensor);
}
else if(cantidadBytes = RS232_PollComport(puertoCom, medicion.h, sizeof(humedad))){
    printf("El sensor es %c\n", medicion.humedad.Lsensor);
}
}
}