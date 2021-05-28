/*
#include <Arduino.h>

void setup()
{
for (int j=2; j<19; j++)
pinMode(j, OUTPUT);
}
void loop()
{
for (int j=2; j<10; j++)
{
digitalWrite(j, HIGH); //Levantamos la columna
for (int k= 10 ; k<18 ; k++)
{
digitalWrite(k, LOW);
delay(250);
digitalWrite(k, HIGH);
}
digitalWrite(j, LOW); //Bajamos la columna
}
}

*/

#include <Arduino.h>
#include <Frequencytimer2.h> // no preguntes de donde salio esta libreria

#define Letra_A {
{0, 0, 0, 1, 1, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 0, 0},
{0, 1, 1, 0, 0, 1, 1, 0}, 
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1}
}
#define Letra_N {
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1},
{1, 1, 1, 0, 0, 0, 1, 1},
{1, 1, 1, 1, 0, 0, 1, 1},
{1, 1, 0, 1, 1, 0, 1, 1},
{1, 1, 0, 0, 1, 1, 1, 1},
{1, 1, 0, 0, 0, 1, 1, 1},
{1, 1, 0, 0, 0, 0, 1, 1}
}

int Letra=0;

#define PINES 17 // cantidad de pines utilizados
#define PULSADOR 1 // pulsador que cambia la letra
#define COLUMNAS 8 
#define FILAS 8
#define Cambia_A 0 // aparece letra A
#define Cambia_N 1 // aparece letra N

byte leds[8][8];
int pin[PINES] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}; // declaracion de todos los pines
int columnas[COLUMNAS] = {pin[13], pin[3], pin[4], pin[10], pin[6], pin[11], pin[15], pin[16]}; // pines de columnas
int filas[FILAS] = {pin[9], pin[14], pin[8], pin[12], pin[1], pin[7], pin[2], pin[5]}; // pines de filas
int pulsador[PULSADOR] = {pin[17]}; // pin de pulsador
const int cambio = 1;

byte cambio1[cambio][8][8] = {Letra_A}; // realiza el encendido de los pines ubicados en las respectivas filas y columnas para aparecer la letra A
byte cambio2[cambio][8][8] = {Letra_N}; //"" letra N

int cambio1 = 0;
int cambio2 = 0;

void setup() {
   
	for(int i = 0; i &lt;=16; i++)
  {
		pinMode(pin[i], OUTPUT);
	}
	for(int i = 0; i &lt;=8; i++)
  {
		digitalWrite(columnas[i - 1], LOW);
	}
	for(int i = 0; i &lt;=8; i++)
  {
		digitalWrite(filas[i - 1], LOW);
}
}

void loop() {

if(Letra == 1)
{
  clearLeds();
  FrequencyTimer2::disable();
  FrequencyTimer2::setPeriod(1000);
  FrequencyTimer2::setOnOverflow(display);
  setCambio1(cambio1);
  delay(250);
}
else if(Letra == 2)
{
  clearLeds();
  FrequencyTimer2::disable();
  FrequencyTimer2::setPeriod(1000);
  FrequencyTimer2::setOnOverflow(display);
  setCambio2(cambio2);
  delay(250);
}

void clearLeds()
{
  for(int i = 0; i &lt; 8; i++)
  {
    for(int j = 0; j &lt; 8; j++)
    {
      leds[i][j] = 0;
    }
  }
}