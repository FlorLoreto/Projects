#include <Time.h>
#include <TimeLib.h>
#include <StopWatch.h>

#include <TimeAlarms.h>

//Handles the intrrupt when pressing the push button.
// Definition of interrupt names
#include <StopWatch.h>

int switchPin = 2;
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 4;
const int buzzPin = 6;
const int desfase = 10;
// We need to declare the data exchange
// variable to be volatile - the value is
// read from memory.
volatile int value;
int redInt = 127;
int greenInt = 127;
int blueInt = 125;
int intbuzzPin = 254;
int alarmTime = 15;
StopWatch reloj(StopWatch::SECONDS);
int alma=0;
int alarmHora = 0;
int alarmSegundo = 5;
int alarmMinuto=0;
int alMinutoDia;
int flag=0;
void Alarma() {
  flag = 1;
  reloj.start();
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);//Open es HIGH 
  pinMode (redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  value=digitalRead(switchPin);
  attachInterrupt( digitalPinToInterrupt(switchPin), ServicioBoton, FALLING); //INT0  Iis Pin 2.
  Serial.printf("Value switchPin inicial %d\n",value);
  setTime(alarmHora, alarmMinuto,  (alarmSegundo-5),15,4,2015);
  alma=Alarm.alarmOnce(alarmHora, alarmMinuto,  alarmSegundo, Alarma);
  
  }

void loop() {
  // put your main code here, to run repeatedly:
  if (value==1) {
    //Serial.printf("Value HIGH! %d\n",value);
    analogWrite(buzzPin, 127);
    //turnOn();
  } else {
    //Serial.printf("Value LOW! %d\n",value);
    
    analogWrite(buzzPin, 0);
  }
  Serial.printf("Value switchPin! %d, VALUE %d\n",digitalRead(switchPin), value);
  delay(1000);
}
// Install the interrupt routine.
void ServicioBoton() {
  // check the value again - since it takes some time to
  // activate the interrupt routine, we get a clear signal.
  reloj.start();
  value = digitalRead(switchPin);//Serial.printf("Service boton\n");Serial.printf("Value! %d\n",value);
  
 }
/*void turnOn() {
  if (reloj.elapsed() <= 5) {
    digitalWrite(redPin, redInt);
    }
  else if (reloj.elapsed() > 5 && reloj.elapsed() <= 10) {
    digitalWrite(greenPin, greenInt);
    digitalWrite(redPin, 0);
    }
  else if (reloj.elapsed() > 10 && reloj.elapsed() <= 15) {
    digitalWrite(bluePin, blueInt);
    digitalWrite(greenPin, 0);
    digitalWrite(redPin, 0);
    }
  else {
    digitalWrite(redPin, 0);
    digitalWrite(bluePin, 0);
    digitalWrite(greenPin, 0);
    reloj.reset();
    analogWrite(buzzPin,0);
     }
}
*/

