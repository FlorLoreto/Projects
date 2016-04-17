#include <Time.h>
#include <TimeLib.h>


// functions to be called when an alarm triggers:

#include <TimeLib.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
StopWatch reloj(StopWatch::SECONDS);
int switchPin = 2;
const int buzzPin = 6;
const int trecePin = 13;
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 4;
const int redInt = 254;
const int greenInt = 254;
const int blueInt = 254;
int volatile value = 0;
long unsigned last_micros = 0;
long unsigned debouncing_time = 15;
long unsigned arranque = 0;
int alarmaDiaria=345;
// ==================  Install the interrupt routine ======================
//-------------------- debounce -------------------------------------------
void debounceInterrupt() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) {

    ServicioBoton();
    last_micros = micros();
  }
}
//---------------------  service routine ------------------------------------
void ServicioBoton() {
  // check the value again - since it takes some time to
  // activate the interrupt routine, we get a clear signal.
  value = 0; Serial.printf("Service boton\n"); Serial.printf("Value! %d\n", value);
  digitalWrite(trecePin, LOW);
  analogWrite(buzzPin, 0);
  // Alarm.disable (Alarm.getTriggeredAlarmId());//if (Alarm.isTriggered()

}
//---------------------  soundAndLight routine ------------------------------------
void soundAndLight() {
  do {
    Serial.printf("tiempo %d\n", reloj.elapsed());
    if (reloj.elapsed() <= 2) {
    analogWrite(redPin, redInt);
      analogWrite(buzzPin, 127);
  }
  else if (reloj.elapsed() > 5 && reloj.elapsed() <= 6) {
    analogWrite(redPin, redInt / 2); analogWrite(greenPin, greenInt / 2);
    analogWrite(buzzPin, 0);
  }
  else if (reloj.elapsed() > 6 && reloj.elapsed() <= 11) {
    analogWrite(greenPin, greenInt);
    analogWrite(redPin, 0);
    analogWrite(buzzPin, 34);
  }
  else if (reloj.elapsed() > 11 && reloj.elapsed() <= 13) {
    analogWrite(greenPin, greenInt / 2); analogWrite(bluePin, blueInt / 2);
    analogWrite(redPin, 0);
    analogWrite(buzzPin, 0);
  }
  else if (reloj.elapsed() > 13 && reloj.elapsed() <= 18) {
    analogWrite(bluePin, greenInt);
    analogWrite(greenPin, 0);
    analogWrite(buzzPin, 205);
  }
  }
  while (reloj.elapsed() < 18 && value == 1);
  pinMode(buzzPin, INPUT_PULLUP);
  value = 0;
   analogWrite(bluePin, 0);
    analogWrite(greenPin, 0);
    analogWrite(redPin, 0);
}
void Alarma() {
value=1;
}

//========================  setup & main ===========================================
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);//Open es HIGH
  pinMode(buzzPin, INPUT_PULLUP);
  pinMode(trecePin, OUTPUT);
  attachInterrupt( digitalPinToInterrupt(switchPin), debounceInterrupt, FALLING); //INT0  Iis Pin 2.
  
   setTime(8,0,0,1,1,2001);
   alarmaDiaria=Alarm.alarmRepeat(8,0,5, Alarma);
   Alarm.enable(alarmaDiaria);
   Serial.printf("alarmaDiaria %d\n",alarmaDiaria);
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf ("seconds %d, value %d \n",second(),value );
  if (value == 1) {
    reloj.start();
    pinMode(buzzPin, OUTPUT);
    soundAndLight();
  }

  pinMode(buzzPin, INPUT_PULLUP);
  reloj.reset();
  Alarm.delay(0);
}
