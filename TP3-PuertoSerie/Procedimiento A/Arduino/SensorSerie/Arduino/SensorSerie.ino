#include <DHT.h>

#define temperatura 1
#define humedad 0

#define POTEPIN A0                                                                                                  //Pin Potenciometro
#define POTEPIN1 A1 
#define DHTPIN 2                                                                                                    //Pin DHT11
#define DHTTYPE DHT11

//Variables:
struct data{
  uint16_t lectura;
  uint32_t tiempo;
};
data datos;
float t = 0.0;
unsigned long tiempoReg;
String datoSensor;
DHT dht(DHTPIN, DHTTYPE);                                                                                           //Definicion pines DHT

void setup(){
  dht.begin();                                                                                                      //Inicializacion DHT
  tiempoReg = millis();
}

void loop(){
  if(Serial.available()>0){
    datoSensor = Serial.readString();                                                                                 //Lectura de letra indicativa
    //Serial.println(datoSensor);
    
    if(datoSensor == "P"){                                                                                            //Segun la letra recibida se lee el sensor deseado
      datos.lectura = lecturaPote();
      Serial.print(datos.lectura); Serial.print("% ");
      tiempo();
    }else if(datoSensor == "R"){
      datos.lectura = lecturaPote1();
      Serial.print(datos.lectura); Serial.print("ohm ");
      tiempo();
    }else if(datoSensor == "T"){
      datos.lectura = lecturaDHT(temperatura);
      Serial.print(datos.lectura); Serial.print("ºC ");
      tiempo();
    }else if(datoSensor == "H"){
     datos.lectura = lecturaDHT(humedad);
     Serial.print(datos.lectura); Serial.print("% ");
     tiempo(); 
    }else Serial.println("Letra no valida.");
  }
  
  if (isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  } 
}

//Funciones:
void tiempo(){                                                                                                //Calcula el tiempo desde la ultima lectura
  datos.tiempo = millis() - tiempoReg;
  tiempoReg = millis();
  Serial.print("-- Tiempo desde ultima lectura: "); Serial.print(datos.tiempo); Serial.println("ms");
}

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
  return(map(analogRead(POTEPIN), 0, 1023, 0, 100));                                                                //Devuelve un %
}

int lecturaPote1(){
  return(analogRead(POTEPIN1));
}
