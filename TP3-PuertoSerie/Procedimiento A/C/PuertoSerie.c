#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "rs-232.h"
#include <stdint.h>

#define LONG_BUFFER 4096

int puertoCOM = 3;
int baudios = 9600;
char modo[] = {'8', 'n', '1', 0};

unsigned long bufferRecepcion[LONG_BUFFER];
int cantidadBytes;
char inicial;

int main(){
	struct sensor{
		uint16_t lectura;
		uint32_t tiempo;
	};
	
	union datos{
		struct sensor dato;
		byte a[sizeof(struct sensor)];
	}lecturas;
	
	if(RS232_OpenComport(puertoCOM, baudios, modo, 0)){
    	printf("No se puedo abrir el puerto COM\n");
    	return 0;
	}
	

	printf("Ingrese la inicial del sensor deseado (P, R, T, H): ");
	
  	while(TRUE){
  		scanf("%c", &inicial);
  		//printf("%c", inicial);
  		if(!strcmp(&inicial, "T")){
  			RS232_SendByte(puertoCOM, 'T');
  		
		}else if(!strcmp(&inicial, "H")){
			RS232_SendByte(puertoCOM, 'H');
  			
		}else if(!strcmp(&inicial, "P")){
			RS232_SendByte(puertoCOM, 'P');
  			
		}else if(!strcmp(&inicial, "R")){
			RS232_SendByte(puertoCOM, 'R');	
		}
		
		cantidadBytes = RS232_PollComport(puertoCOM, lecturas.a, sizeof(struct sensor)-1);
		if(cantidadBytes > 1){
			lecturas.a[cantidadBytes] = 0;
  			printf("Lectura de %c :%d\n", inicial, lecturas.dato.lectura);
  			printf("Tiempo desde ultima lectura: %lu\n", lecturas.dato.tiempo);
  			cantidadBytes = 0;
 		}
}
		
}
