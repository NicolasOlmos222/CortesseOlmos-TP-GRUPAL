#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <Windows.h>
#include "rs-232.h"

#define LONG_BUFFER 4096

int puertoCOM=3;             																	//Seleccion de puerto
int baudios=9600;            																	//Velocidad en baudios
char modo[]={'8','N','1',0}; 																	// 8 bits de datos, no paridad, 1 bit de parada

unsigned char bufferRecepcion[LONG_BUFFER];
char inicial;
int cantidadBytes;
  
int main(){
	if(RS232_OpenComport(puertoCOM, baudios, modo, 0)){											//Prueba de puerto
    	printf("No se puede abrir el puerto COM\n");
    	return(0);
  	}
	printf("Ingrese la inicial del sensor deseado (P, R, T, H): ");
	
  	while(TRUE){
  		scanf("%c", &inicial);
  		//printf("%c", inicial);
  		if(!strcmp(&inicial, "T")){
  			RS232_SendByte(puertoCOM, 'T');
  			cantidadBytes = RS232_PollComport(puertoCOM, bufferRecepcion, LONG_BUFFER-1);
  			if(cantidadBytes > 0){
      			bufferRecepcion[cantidadBytes] = 0;   // Poner un NULL al final del string
				printf("%s\n", (char *)bufferRecepcion);
				printf("Ingrese la inicial del sensor deseado (P, R, T, H): ");
    		}
		}else if(!strcmp(&inicial, "H")){
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
    		}
		}
	}
}
