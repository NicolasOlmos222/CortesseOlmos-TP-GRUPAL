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
      Serial.println(datos.lectura);
      tiempo();
    }else if(datoSensor == "R"){
      datos.lectura = lecturaPote1();
      Serial.println(datos.lectura);
      tiempo();
    }else if(datoSensor == "T"){
      datos.lectura = lecturaDHT(temperatura);
      Serial.println(datos.lectura);
      tiempo();
    }else if(datoSensor == "H"){
     datos.lectura = lecturaDHT(humedad);
     Serial.println(datos.lectura);
     tiempo(); 
    }else Serial.println("X");
  }
}

//Funciones:
void tiempo(){                                                                                                //Calcula el tiempo desde la ultima lectura
  datos.tiempo = millis() - tiempoReg;
  tiempoReg = millis();
  Serial.println(datos.tiempo);
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
