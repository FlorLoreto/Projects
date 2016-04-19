/*
 * TimeAlarmExample.pde
 *
 * This example calls alarm functions at 8:30 am and at 5:45 pm (17:45)
 * and simulates turning lights on at night and off in the morning
 * A weekly timer is set for Saturdays at 8:30:30
 *
 * A timer is called every 15 seconds
 * Another timer is called once only after 10 seconds
 *
 * At startup the time is set to Jan 1 2011  8:29 am
 */
 
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
StopWatch reloj(StopWatch::SECONDS);
AlarmId alar;
AlarmId alar1;
int switchPin = 2;
const int buzzPin = 6;
int volatile value;
long unsigned last_micros=0;
long unsigned debouncing_time=15;
void setup()
{
  Serial.begin(9600);
  setTime(8,29, 55,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011
  // create the alarms 
 alar= Alarm.alarmRepeat(8,30,0, MorningAlarm); 
 alar1= Alarm.alarmRepeat(8,30,0, MorningAlarm);// 8:30am every day
  //attachInterrupt( digitalPinToInterrupt(switchPin), debounceInterrupt, FALLING); 
 }

void  loop(){  
  Serial.printf ("segundos %d \n",second());
  Alarm.delay(0); // wait one second between clock display
  if (value==1) {
  Serial.printf("Alarm: - turn lights off %s", alar);
   reloj.start();
    while (reloj.elapsed() < 5) {
    analogWrite(buzzPin, 127);
     Serial.printf("Alarma!!!!\n");
   }
   value=0;
   analogWrite(buzzPin, 0);
  }
  
  
  }


// functions to be called when an alarm triggers:
void MorningAlarm(){
  value=1;
  Serial.print("alarmtrigered \n");Serial.println(alar);
  Serial.print("alarmtrigered1 \n");Serial.println(alar1);
}
// ==================  Install the interrupt routine ======================
//-------------------- debounce -------------------------------------------
void debounceInterrupt() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) {

    ServicioBoton();
    last_micros = micros();
   }
}
void debuzzing(){
  
  }
//---------------------  service routine ------------------------------------
void ServicioBoton() {
  // check the value again - since it takes some time to
  // activate the interrupt routine, we get a clear signal.
  value = digitalRead(switchPin); Serial.printf("Service boton\n"); Serial.printf("Value! %d\n", value);
  analogWrite(buzzPin, 0);
   Alarm.disable  (Alarm.getTriggeredAlarmId());//if (Alarm.isTriggered()
 
}

