#include <stdio.h>
#include <stdlib.h>

int main(){
 	FILE *archivo;
 	char caracteres[100];
 	archivo = fopen("LECTUR.BIN","r");																//Se abre el archivo						
 	
 	if (archivo == NULL){																			//Comprobacion
 	 	printf("\nEl archivo no se encontro \n\n");
		exit(1);	
	} else{
 	    printf("\nEl contenido del archivo es: \n\n");
 	    printf("sensor		lectura		diferencia de tiempo \n");
 	    while (feof(archivo) == 0){																	//Se imprimen los datos
 			fread(caracteres, sizeof (char), 1, archivo);
 			printf("%s", caracteres);
 		}     
    }
    fclose(archivo);
    printf("h: humedad [porcentaje]\nt: temperatura [*C]\nr: resistencia [ohm]\np: porcentaje de potenciometro [porcentaje]\n");
    system("PAUSE");
	return 0;
}

