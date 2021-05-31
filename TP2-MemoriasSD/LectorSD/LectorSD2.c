#include <stdio.h>
#include <stdlib.h>

int main(){
 	FILE *archivo;
 	char caracteres[100];
 	archivo = fopen("LECTUR.BIN","r");
 	
 	if (archivo == NULL){
 	 	printf("\nEl archivo no se encontro \n\n");
		exit(1);	
	} else{
 	    printf("\nEl contenido del archivo es: \n\n");
 	    printf("sensor		lectura		diferencia de tiempo \n");
 	    while (feof(archivo) == 0){
 			fread(caracteres, sizeof (char), 1, archivo);
 			printf("%s", caracteres);
 		}     
    }
    fclose(archivo);
    printf("h: humedad [porcentaje]\nt: temperatura [*C]\nr: resistencia [ohm]\np: porcentaje de potenciometro [porcentaje]\ndifer de tiempo: ms");
    system("PAUSE");
	return 0;
}

