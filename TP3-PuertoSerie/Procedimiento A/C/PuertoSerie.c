#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "rs-232.h"

#define LONG_BUFFER 4096

int puertoCOM = 3;
int baudios = 9600;
char modo[] = {'8', 'n', '1', 0};

unsigned char bufferRecepcion[LONG_BUFFER];
int cantidadBytes;
char inicial;

int main(){
	if(RS232_OpenComport(puertoCOM, baudios, modo, 0)){
    	printf("No se puedo abrir el puerto COM\n");
    	return 0;
	}
	
	typedef struct {
    unsigned long tiempo;
    int sensor;
    char Lsensor;
}temperatura, humedad;

union temperatura{
    temperatura dato;
    byte t[sizeof(temperatura)];
}medicion;

/*union humedad{
    temperatura dato;
    byte h[sizeof(humedad)];
}medicion;*/

	printf("Ingrese la inicial del sensor deseado (P, R, T, H): ");
	
  	while(TRUE){
  		scanf("%c", &inicial);
  		//printf("%c", inicial);
  		if(!strcmp(&inicial, "T")){
  			RS232_SendByte(puertoCOM, 'T');
  			if(cantidadBytes = RS232_PollComport(puertoCOM, medicion.t, sizeof(temperatura))){
    		printf("El sensor es %c\n", temperatura.tiempo);
}
    }
		/*}else if(!strcmp(&inicial, "H")){
			RS232_SendByte(puertoCOM, 'H');
  			cantidadBytes = RS232_PollComport(puertoCOM, bufferRecepcion, LONG_BUFFER-1);
  			if(cantidadBytes > 0){
      			bufferRecepcion[cantidadBytes] = 0;   // Poner un NULL al final del string
				printf("%s\n", (char *)bufferRecepcion);
				printf("Ingrese la inicial del sensor deseado (P, R, T, H): ");
    		}
		}else if(!strcmp(&inicial, "P")){
			RS232_SendByte(puertoCOM, 'P');
  			cantidadBytes = RS232_PollComport(puertoCOM, bufferRecepcion, LONG_BUFFER-1);
  			if(cantidadBytes > 0){
      			bufferRecepcion[cantidadBytes] = 0;   // Poner un NULL al final del string
				printf("%s\n", (char *)bufferRecepcion);
				printf("Ingrese la inicial del sensor deseado (P, R, T, H): ");
    		}
		}else if(!strcmp(&inicial, "R")){
			RS232_SendByte(puertoCOM, 'R');
  			cantidadBytes = RS232_PollComport(puertoCOM, bufferRecepcion, LONG_BUFFER-1);
  			if(cantidadBytes > 0){
      			bufferRecepcion[cantidadBytes] = 0;   // Poner un NULL al final del string
				printf("%s\n", (char *)bufferRecepcion);
				printf("Ingrese la inicial del sensor deseado (P, R, T, H): ");
    		}*/
		}
	
}
