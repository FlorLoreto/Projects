/*
   TimeAlarmExample.pde

   This example calls alarm functions at 8:30 am and at 5:45 pm (17:45)
   and simulates turning lights on at night and off in the morning
   A weekly timer is set for Saturdays at 8:30:30

   A timer is called every 15 seconds
   Another timer is called once only after 10 seconds

   At startup the time is set to Jan 1 2011  8:29 am
*/

#include <TimeLib.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
StopWatch reloj(StopWatch::SECONDS);
int switchPin = 2;
const int buzzPin = 13;
int volatile value;
void MorningAlarm() {
  value = 1;
 }
void setup()
{
  Serial.begin(9600);
  setTime(8, 29, 55, 1, 1, 11); // set time to Saturday 8:29:00am Jan 1 2011
  // create the alarms
  pinMode(switchPin, INPUT_PULLUP);
   pinMode(buzzPin, OUTPUT);
  Alarm.alarmRepeat(8, 30, 0, MorningAlarm); // 8:30am every day
  value = digitalRead(switchPin);
  reloj.reset(); value=0;
}

void  loop() {
  Serial.printf ("value %d\n", value);
  Serial.printf ("segundos %d \n", second());
   // wait one second between clock display
  if (value == 1) {reloj.start();
  while (reloj.elapsed()<15){
  Serial.println("Alarm: - turn lights off");
 
 digitalWrite(buzzPin, HIGH);
  Serial.printf("Alarma!!!!\n");
  }
  Serial.printf("final alarma %d\n",reloj.elapsed());
 value = 0;
  digitalWrite(buzzPin, LOW);
  reloj.reset();
  }
  
  Alarm.delay(0);
}




