#include <SPI.h>		// incluye libreria interfaz SPI
#include <SD.h>			// incluye libreria para tarjetas SD

#define SSpin 53		// Slave Select en pin digital 53

FILE * ptr;          // puntero del archivo
ptr = fopen("PRUEBA2.txt", "r");		// definimos el archivo a abrir para su lectura unicamente

void setup() {
  Serial.begin(9600);				// inicializa monitor serie a 9600 bps
  Serial.println("Inicializando tarjeta ...");
  if (!SD.begin(SSpin)) {			// inicializacion de tarjeta SD
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;					// se sale del setup() para finalizar el programa
  }
  Serial.println("Inicializacion correcta");	// texto de inicializacion correcta

  archivo = SD.open(ptr);		// apertura de archivo
  if (archivo) {
    Serial.println(ptr);	// texto en monitor serie
    while (archivo.available()) {		// mientras exista contenido en el archivo
      Serial.write(archivo.read());  		// lectura de a un caracter por vez
    }
    archivo.close();				// cierre de archivo
  } else {
    Serial.println("Error en la apertura de prueba.txt");// texto de falla en apertura de archivo
  }
}

void loop() {			// funcion loop() obligatoria de declarar pero no utilizada
}