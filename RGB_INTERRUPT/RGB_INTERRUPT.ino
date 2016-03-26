#include <Time.h>
#include <TimerOne.h>


//Programa que enciende sucesivamente un LED RGB en cada uno de ssus colores
//Se introducen por consola serial los valores de los pines a que
//se conecta y los valores del ciclo de trabajo para su fucinamiento
//como PWM en analogWrite(pin, value) con value<=255. Los únicos
//pines con esta función son 3, 5, 6, 9, 10, y 11.

//***************************************************************

// 1ª Parte: declaración de variables

//A) Nº de los puertos conectados a los pines.
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

//B) Las intensidades de cada color dadas por el ciclo de trabajo del PWM

const int redInt = 254;
const int greenInt = 254;
const int blueInt = 255;

//C) El tiempo de encendido de cada color en milisegundos:

int redMil = 1000;
int greenMil = 1000;
int blueMil = 5000;

//D) El tiempo de apagado em milisegundos

int apagaLed = 5000;
unsigned long currentMillis;
unsigned long previousMillis;
//E) la variable volátil para intercambiar;
volatile int flag;
int k=0;
// En el setup inicializo el Serial Monitor y pongo los pines en modo salida

void setup() {

  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Timer1.initialize(1000000);         // initialize timer1, and set a 1 second period
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}
  
 
void loop() {
  currentMillis = millis();//millis() mide el tiempo en milisegundos desde el comienzo del programa
  
  //Apago todos los colores
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  //indico que están apagados
  String redState = "LOW";
  String greenState = "LOW";
  String blueState = "LOW";
  //Calling functions
  switch (flag) {
    case 0:
      analogWrite(redPin, redInt);
      break;
    case 1:
      analogWrite(redPin, 0);
      break;
    case 2:
      analogWrite(greenPin, greenInt);
      break;
     case 3:
      analogWrite(greenPin, 0);
      break;
     case 4:
      analogWrite(bluePin, blueInt);
      break;
     case 5:
      analogWrite(bluePin, 0);
      break;
    default: 
      analogWrite(bluePin, blueInt^1);
    break;
  }
 
}
//Function callback()
void callback()
{
  k=k+1;
  flag=k%6;
  //0: red
  //1:green
  //2:blue
}



