//This sketch will handle an Alarm Clock
//import libraries
//include libraries
#include <Time.h>
#include <TimeAlarms.h>
#include <TimerOne.h>
// 1. Variables declaration
int semDia;// Day of the week, Sunday is day 1
int dia;//Day
int mes; //Month
int anyo;//Year
int hora;//Hour
int minutos;//Minutes
int redPin;//Digital pin for red ligth
int greenPin;//Digital pin for green ligth
int bluePin;//Digital pin for blue ligth
int buzzerPin;//Digital pin for buzzer
int blinkRate;//Milliseconds the ligth is on or off
int pitchCycle;//Duty cycle of the PWM
int switchPin;//Digital pin to check the switch state
int alarmaHora;//Alarm hour
int alarmaMinutos;//Alarm minutes
volatile int flag;
int k;
unsigned long interval;
long unsigned previousMillis;
long unsigned currentMillis;

/*
  Alarm is always programmed from Monday (weekday 2) to Friday (weekday 6)
*/
void setup() {
  // put your setup code here, to run once:
  dia = 28;
  mes = 3;
  anyo = 16;
  hora = 17;
  minutos = 18;
  alarmaHora = hora;// para pruebas
  alarmaMinutos = minutos+1;//para pruebas
  redPin = 9;
  greenPin = 10;
  bluePin = 11;
  blinkRate = 1000;
  buzzerPin = 3;
  pitchCycle = 127;
  switchPin = 2;
  k = 0;
  
  interval = 1000; //milliseconds
  previousMillis = 0;
  // select pinModes
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  //free pins and switchPin are turned into Pull-up mode
  //pinMode(!redPin && !greenPin && !bluePin && !buzzerPin, INPUT_PULLUP);
//  analog pins turned into pull-up mode too
 /* for (int r = A0; r <= A5; r++) {
  digitalWrite(r, HIGH);
  }*/
  Timer1.initialize(1000000);         // initialize timer1, and set a 1 second interval
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
  Serial.begin(9600);
  //LigthColor(255,0,0);
  setTime(hora, minutos, 0, dia, mes, anyo); setTime(17, 18, 15, 28, 3, 16);
  semDia = weekday();
  currentMillis = millis();
}
/*
  main loop
*/
void loop() {
  // If Alarm is set, sound
    /*Alarm.alarmRepeat(dowMonday, alarmaHora, alarmaMinutos, 0, alarma);*/Alarm.alarmRepeat(dowMonday,17,18,20,alarma);Alarm.alarmRepeat(dowTuesday,17,18,20,alarma);  
   /* Alarm.alarmRepeat(dowTuesday, alarmaHora, alarmaMinutos, 0, alarma);Alarm.alarmRepeat(dowMonday,17,18,20,alarma); 
    Alarm.alarmRepeat(dowWednesday, alarmaHora, alarmaMinutos, 0, alarma);
    Alarm.alarmRepeat(dowThursday, alarmaHora, alarmaMinutos, 0, alarma);
    Alarm.alarmRepeat(dowFriday, alarmaHora, alarmaMinutos, 0, alarma); //Create an alarm that will call a function every week on a specific day at a particular time.
    // "dayofweek" can be dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, or dowSaturday.
    /*Alarm.alarmRepeat(dowMonday, alarmaHora, alarmaMinutos, 0, noAlarma);
    Alarm.alarmRepeat(dowTuesday, alarmaHora, alarmaMinutos, 0, noAlarma);
    Alarm.alarmRepeat(dowWednesday, alarmaHora, alarmaMinutos, 0, noAlarma);
    Alarm.alarmRepeat(dowThursday, alarmaHora, alarmaMinutos, 0, noAlarma);
    Alarm.alarmRepeat(dowFriday, alarmaHora, alarmaMinutos, 0, noAlarma);*/
 currentMillis = millis();
  if ((millis() - previousMillis) >= interval)
  {
   showTime();
   previousMillis = currentMillis;
  }
}
/*
  Function showTime()
*/
void showTime() {
  Serial.print("Date:"); Serial.print(year()); Serial.print("/"); Serial.print(month()); Serial.print("/"); Serial.println(day());Serial.printf("\t");Serial.println(weekday());
  Serial.print("hour:"); Serial.print(hour()); Serial.print(":"); Serial.print(minute()); Serial.print(":"); Serial.println(second());
}
//Function alarma()

void alarma(){
  analogWrite(3,  127);
  }
//Function callback()
void callback()
{
  k = k + 1;
  flag = k % 6;
  //0: red
  //1:green
  //2:blue
}
