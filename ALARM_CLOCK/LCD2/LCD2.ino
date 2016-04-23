#include <Event.h>
#include <Timer.h>

#include <TimeAlarms.h>
/*
  LiquidCrystal Library - FormatText
*/
#include <LiquidCrystal.h> // include the library code:
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <elapsedMillis.h>
//constants for the number of rows and columns in the LCD
const int numRows = 2;
const int numCols = 16;
int count;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
elapsedMillis timer;
#define interval 1000
void setup()
{Serial.begin(9600);
  lcd.begin(numCols, numRows);
  lcd.clear();
  lcd.print("Alarma "); // this string is 8characters long
  lcd.setCursor(0, 1);
  lcd.print("Hora: ");
   setTime(8,29, 55,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011
  // create the alarms 
  Alarm.alarmRepeat(8,30,0, MorningAlarm); 
  timer = 0;
  for (int i=A0;i<A6;++i){
    digitalWrite(A0, HIGH);}

   pinMode(7, INPUT_PULLUP);}


void loop()
{
  lcd.setCursor(7, 0);//Position the LCD cursor; that is, set the location at which subsequent text written to the LCD will be displayed.
  if (Alarm.getTriggeredAlarmId() != 0) {
    lcd.print("ON");
    Serial.printf("alarmtriggered %d \n",Alarm.getTriggeredAlarmId());
  }
  else {
    lcd.print("OFF");
  }
  lcd.setCursor(6, 1);
  lcd.print(hour());lcd.print(":");lcd.print(minute());lcd.print(":");lcd.print(second());

Alarm.delay(1000);
}
void MorningAlarm(){
  Serial.println("dispara alarma!");
  Serial.printf("alarma triggerada %d \n",Alarm.getTriggeredAlarmId());
}
