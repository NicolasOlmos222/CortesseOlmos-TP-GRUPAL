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
  String nombre;
};
data datos;

union dt{
  unsigned long valor;
  byte b[7];
}a, c;

float t = 0.0;
unsigned long tiempoReg;
String datoSensor;
DHT dht(DHTPIN, DHTTYPE);                                                                                           //Definicion pines DHT
void setup(){
  dht.begin();                                                                                                      //Inicializacion DHT
  tiempoReg = millis();
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()>0){
    datoSensor = Serial.readString();                                                                                 //Lectura de letra indicativa
    //Serial.println("OK");
    //Serial.println(datoSensor);
    
    if(datoSensor == "P"){                                                                                             //Segun la letra recibida se lee el sensor deseado
      datos.nombre = "P";
      datos.lectura = lecturaPote();

      //Envio:
      //Serial.println(datos.nombre);
      envioDato();
      tiempo();
      
    }else if(datoSensor == "R"){
      datos.lectura = lecturaPote1();
      
      //Envio:
      //Serial.println(datos.nombre);
      envioDato();
      tiempo();
      
    }else if(datoSensor == "T"){
      datos.lectura = lecturaDHT(temperatura);
      
      //Envio:
      //Serial.println(datos.nombre);
      envioDato();
      tiempo();
      
    }else if(datoSensor == "H"){
     datos.lectura = lecturaDHT(humedad);
     
     //Envio:
      //Serial.println(datos.nombre);
      envioDato();
      tiempo();
      
    }//else Serial.println("Letra no valida.");
  }
}

//Funciones:
void tiempo(){                                                                                                //Calcula el tiempo desde la ultima lectura
  datos.tiempo = millis() - tiempoReg;
  tiempoReg = millis();
  //Serial.println(datos.tiempo); Serial.println("ms");
  a.valor = datos.tiempo;
  //Serial.println(a.valor);    
  for(int y=0 ; y < sizeof(a.valor) ; y++){
    Serial.write(a.b[y]);
  }
}

void envioDato(){
  a.valor = datos.lectura;
  //Serial.println(a.valor);    
  for(int y=0 ; y < sizeof(a.valor) ; y++){
    Serial.write(a.b[y]);
    //c.b[y] = a.b[y];
  }   
  /*for(unsigned long long i = 0; i < (sizeof(c.b));i++){
    Serial.write(c.b[i]);
  }*/
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
