
//include libraries
#include <Chrono.h>
#include <LightChrono.h>
#include <Time.h>
#include <TimeAlarms.h>

//declare variables
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int buzzerPin = 3;
int switchPin=2;
//El tiempo de encendido de cada color en milisegundos:
unsigned int flag;
int k = 0;
unsigned int m = 0;
int dutyCycle = 127;
unsigned long currentMillis;
unsigned long tiempoTranscurrido;
int repeatTimes = 2;
void(* resetFunc) () = 0;
int volatile state=0;
/*
  setup
*/


void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
  /*
    Set date-time
  */
  setTime(18, 15, 0, 29, 3, 2016);
  /*
  switch
  */
  
attachInterrupt(switchPin, resetFunc, RISING);

  // Start the chronometer on setup.
   Chrono myChrono(Chrono::SECONDS);
}
/*
  main
*/
void loop()
{
  Alarm.alarmRepeat(18, 15, 5, Alarma);
 Serial.print("hora actual "); Serial.print(hour()); Serial.print(minute()); Serial.println(second());
state=digitalRead(switchPin);
Serial.print("switichPin  ");Serial.println(state);
 Alarm.delay(0);//necessary
}




