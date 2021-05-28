#include <DHT.h>                                                                                                    //Libreria sensor de temperatura DHT11
#include <SD.h>                                                                                                     //Libreria lector SD
#include "antiRebote.h"                                                                                             //Libreria local

#define temperatura 1
#define humedad 0

#define POTEPIN A0                                                                                                  //Pin potenciometro
#define POTEPIN1 A1                                                                                                 //Pin pote 2
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
unsigned long lecturaTiempo;
File logFile;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pulsador_config();                                                                                                  //Setup antiRebote
  Serial.begin(9600);
  dht.begin();                                                                                                        //Inicializacion DHT
  
  Serial.println(F("Inicializando lector SD.."));
  if (!SD.begin(4)){                                                                                                  //Comprueba tarjeta de memoria
    Serial.println(F("Error al iniciar lector SD"));
    return;
  } Serial.println(F("Lector SD iniciado correctamente"));

  lecturaTiempo = millis();
}

void loop() {
  if(pulsador_cicloA ()){                                                                                             //Lee los sensores y los escribe solo cuando se acciona el pulsador
    for(int i=0; i < 4; i++){                                                                                         //Un ciclo por sensor
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
          if (isnan(t)) {
            Serial.println("Error obteniendo los datos del sensor DHT11");
            return;
          }
          Serial.print(datos.lectura); Serial.print(" ");
        break;
        case 3:
          datos.lectura = lecturaDHT(humedad);
          if (isnan(t)) {
            Serial.println("Error obteniendo los datos del sensor DHT11");
            return;
          }
          Serial.print(datos.lectura); Serial.print(" ");
        break;
      }
      
      datos.tiempo = millis() - lecturaTiempo;
      lecturaTiempo = millis();
      Serial.print(datos.tiempo); Serial.println("");

      logFile = SD.open("prueba.txt", FILE_WRITE);                                                                    //Guarda la lectura actual
      if(logFile){      
        logFile.print(datos.tipo);      logFile.print(" ");  
        logFile.print(datos.lectura);   logFile.print(" ");  
        logFile.println(datos.tiempo);
        logFile.close();
      } else Serial.println("Error al abrir el archivo");
    }
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
  return(map(analogRead(POTEPIN), 0, 1023, 0, 100));                                                                    //Devuelve un porcentaje
}

uint16_t lecturaPote1(){
  return(analogRead(POTEPIN1) * (5.0 / 1023.0));                                                                        //Devuelve el voltaje medido
}
