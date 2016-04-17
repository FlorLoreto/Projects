#include <Time.h>
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
int alarmaDiaria = 345;
boolean alarmState = true;
boolean lastAlarmState = true;
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
  value = 0;
  // Alarm.disable (Alarm.getTriggeredAlarmId());//if (Alarm.isTriggered()
  if (lastAlarmState == true)  {
    Alarm.disable(alarmaDiaria); alarmState = false;
  }
    else            {
      Alarm.enable(alarmaDiaria);
      alarmState = true;
    }
    Serial.printf("states of alarm %d\n", alarmState); 
    lastAlarmState = alarmState;
  }

  //---------------------  soundAndLight routine ------------------------------------
  void soundAndLight() {
    Serial.print ("Luz y Sonido no son ruido");
  }
  void Alarma() {
    value = 1;
  }

  //========================  setup & main ===========================================
  void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(switchPin, INPUT_PULLUP);
    attachInterrupt( digitalPinToInterrupt(switchPin), debounceInterrupt, FALLING); //INT0  Iis Pin 2.
    setTime(8, 0, 0, 1, 1, 2001);
    alarmaDiaria = Alarm.alarmRepeat(8, 0, 5, Alarma);
    Alarm.enable(alarmaDiaria); alarmState = true;
    lastAlarmState = alarmState;

  }
  void loop() {
    // put your main code here, to run repeatedly:
    Serial.printf("State %d\n", alarmState);
    if (value == 1) {
      reloj.start();
      soundAndLight();
    }

    pinMode(buzzPin, INPUT_PULLUP);
    reloj.reset();
    Alarm.delay(0);
  }
