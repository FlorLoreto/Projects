
// functions to be called when an alarm triggers:

#include <TimeLib.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
StopWatch reloj(StopWatch::SECONDS);
int switchPin = 2;
const int buzzPin = 13;
int volatile value = 1;
long unsigned last_micros = 0;
long unsigned debouncing_time = 15;
long unsigned arranque = 0;
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
  digitalWrite(buzzPin, LOW);
  // Alarm.disable (Alarm.getTriggeredAlarmId());//if (Alarm.isTriggered()

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);//Open es HIGH
  pinMode(buzzPin, OUTPUT);
  value = digitalRead(switchPin);
  attachInterrupt( digitalPinToInterrupt(switchPin), debounceInterrupt, FALLING); //INT0  Iis Pin 2.
}

void loop() {
  // put your main code here, to run repeatedly:
  if (value == 1) {
    reloj.start();
  }
  do {
    Serial.printf("tiempo %d\n", reloj.elapsed());
    digitalWrite(buzzPin, HIGH);
  }
  while (reloj.elapsed() < 15/*&&value == 1*/);
  
 digitalWrite(buzzPin, LOW);

reloj.reset();
value=0;
}
