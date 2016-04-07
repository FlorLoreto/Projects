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
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int buzzPin = 3;

//B) Las intensidades de cada color dadas por el ciclo de trabajo del PWM

const int redInt = 254;
const int greenInt = 254;
const int blueInt = 255;

//E) la variable volátil para intercambiar;
volatile int flag;
int k=0;
// En el setup inicializo el Serial Monitor y pongo los pines en modo salida

void setup() {

   // attaches callback() as a timer overflow interrupt
}
  
 
 
  //Apago todos los colores
  
  //Calling functions
 //Function callback()
void callback()
{
  k=k+1;
  flag=k%6;
  //0: red
  //1:green
  //2:blue
   
}
//
void Alarma(){
switch (flag) {
    case 0:
      analogWrite(redPin, redInt);
      analogWrite(buzzPin, 0);
      break;
    case 1:
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
       analogWrite(buzzPin, 255);
    break;
    case 2:
      analogWrite(greenPin, greenInt);
      analogWrite(buzzPin, 0);
      break;
     case 3:
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      analogWrite(buzzPin, 127);
     break;
     case 4:
      analogWrite(bluePin, blueInt);
      analogWrite(buzzPin, 0);
      break;
     case 5:
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      analogWrite(buzzPin, 65);
      
      break;
    default: 
      analogWrite(bluePin, blueInt^1);
    break;
  }
}

