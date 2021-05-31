#include <DHT.h>                                                                                                    //Libreria sensor de temperatura DHT11
#include <SD.h>  
#include "antiRebote.h"  

#define temperatura 1
#define humedad 0

#define POTEPIN A0                                                                                                  //Pin Potenciometro
#define POTEPIN1 A1 
#define DHTPIN 2                                                                                                    //Pin DHT11
#define DHTTYPE DHT11

//Variables:
struct data{
  char tipo;
  uint16_t lectura;
  uint32_t tiempo;
};
data datos;
char letra[4] = {'p', 'r', 't', 'h'};
float t = 0.0;

File logFile;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pulsador_config();
  Serial.begin(9600);
  dht.begin();
  
  Serial.println(F("Inicializando lector SD.."));
  if (!SD.begin(4)){
    Serial.println(F("Error al iniciar lector SD"));
    return;
  } Serial.println(F("Lector SD iniciado correctamente"));
}

void loop() {
  if(pulsador_cicloA ()){   
    datos.tiempo = millis() - datos.tiempo;
    for(int i=0; i < 4; i++){
      datos.tipo = letra[i];
      Serial.print(datos.tipo); Serial.print(" ");
      
      switch (i){
        case 0:
          datos.lectura = lecturaPote();
          Serial.print(datos.lectura); Serial.print(" ");
        break;
        case 1:
          datos.lectura = lecturaPote1();
          Serial.print(datos.lectura); Serial.print(" ");
        break;
        case 2:
          datos.lectura = lecturaDHT(temperatura);
          Serial.print(datos.lectura); Serial.print(" ");
        break;
        case 3:
          datos.lectura = lecturaDHT(humedad);
          Serial.print(datos.lectura); Serial.print(" ");
        break;
      }
      Serial.print(datos.tiempo); Serial.println("");
      logFile = SD.open("Lectur.bin", FILE_WRITE);
      if(logFile){      
        logFile.print(datos.tipo);      logFile.print("   ");  
        logFile.print(datos.lectura);   logFile.print("   ");  
        logFile.println(datos.tiempo);
        logFile.close();
      } else Serial.println("Error al abrir el archivo");
    }
  }   
  if (isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  } 
}

//Funciones:
float lecturaDHT(bool modo){
  switch(modo){
    case temperatura:
      t = dht.readTemperature();
    break;
    case humedad:
      t = dht.readHumidity();
    break;
  }
  return(t);
}

int lecturaPote(){
  return(map(analogRead(POTEPIN), 0, 1023, 0, 100));
}

int lecturaPote1(){
  return(analogRead(POTEPIN1));
}
