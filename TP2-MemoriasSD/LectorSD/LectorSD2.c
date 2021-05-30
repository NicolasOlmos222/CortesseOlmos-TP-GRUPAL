#include <stdio.h>

int main() {
    FILE *fpt;
fpt = fopen("PRUEBA2.bin", "r");
if(fpt == NULL){
printf("No se pudo abrir el archivo");
return -1;
}

fclose(fpt);
printf("\nSe ha leido el archivo correctamente");

return 0;

}