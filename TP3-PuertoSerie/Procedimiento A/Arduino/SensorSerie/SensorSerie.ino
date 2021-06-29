#include <DHT.h>

#define temperatura 1
#define humedad 0

#define POTEPIN A0                                                                                                  //Pin Potenciometro
#define POTEPIN1 A1 
#define DHTPIN 2                                                                                                    //Pin DHT11
#define DHTTYPE DHT11

//Variables:
struct data{
  uint32_t tiempo;
  uint16_t lectura;
  String nombre;
};
data datos;
float t = 0.0;
unsigned long tiempoReg;
String datoSensor;
DHT dht(DHTPIN, DHTTYPE);                                                                                           //Definicion pines DHT
int i;
void setup(){
  dht.begin();                                                                                                      //Inicializacion DHT
  tiempoReg = millis();
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()>0){
    datoSensor = Serial.readString();                                                                                 //Lectura de letra indicativa
    //Serial.print("OK");
    //Serial.println(datoSensor);
    if(datoSensor == "P"){                                                                                             //Segun la letra recibida se lee el sensor deseado
      datos.nombre = "PYHJG";
      datos.lectura = String lecturaPote();
      tiempo();
      for(i = 0; i < sizeof(datos.nombre);i++){
        Serial.print(datos.nombre[i]);
      }
      for(i = 0; i < sizeof(datos.lectura);i++){
        Serial.print(datos.lectura[i]);
      }
      for(i = 0; i < sizeof(datos.tiempo);i++){
        Serial.print(datos.tiempo[i]);
      }
    }else if(datoSensor == "R"){
      datos.lectura = lecturaPote1();
      Serial.print(datos.lectura); //Serial.print("ohm ");
      tiempo();
    }else if(datoSensor == "T"){
      datos.lectura = lecturaDHT(temperatura);
      Serial.print(datos.lectura); //Serial.print("C ");
      tiempo();
    }else if(datoSensor == "H"){
     datos.lectura = lecturaDHT(humedad);
     Serial.print(datos.lectura); //Serial.print("% ");
     tiempo(); 
    }//else Serial.println("Letra no valida.");
  }
}

//Funciones:
void tiempo(){                                                                                                //Calcula el tiempo desde la ultima lectura
  datos.tiempo = millis() - tiempoReg;
  tiempoReg = millis();
  Serial.println(datos.tiempo);// Serial.println("ms");
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
