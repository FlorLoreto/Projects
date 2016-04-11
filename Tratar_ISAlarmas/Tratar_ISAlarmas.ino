#include <Time.h>
#include <TimeAlarms.h>
#include <avr/wdt.h>
#include <TimerOne.h>
#include <StopWatch.h>
int dia = 8;
int mes = 4;
int anyo = 2016;
int hora = 0;
int minuto = 0;
int segundo = 0;
int alarmMinuto = 0;
int alarmHora = 0;
int alarmSegundo = 0;
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int buzPin = 3;

long unsigned ante_Millis = 0;
long unsigned actual_Millis;
long unsigned intervalo = 1500;
long unsigned ante_Millis1 = 0;
long unsigned actual_Millis1;
long unsigned intervalo1 = 5;
int flag[7];
int redInt = 127;
int greenInt = 127;
int blueInt = 125;
int intBuzPin = 254;
int alarmTime = 15;
StopWatch reloj(StopWatch::SECONDS);



void Alarma() {
  boolean available();
  long unsigned tiempo = now();

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setTime(hora, minuto, segundo, dia, mes, anyo);
  int ID1= Alarm.alarmRepeat(alarmHora, alarmMinuto,  alarmSegundo + 5, MorningAlarm1);
  int ID2=Alarm.alarmRepeat(alarmHora, alarmMinuto,  alarmSegundo + 30, MorningAlarm2);
  pinMode (buzPin, OUTPUT);
  pinMode (redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  /*ID = Alarm.timerOnce(60, spinning);

  disable(ID1);  //-  prevent the alarm associated with the given ID from triggering   
  enable(ID1); */
}

void loop() {
  // put your main code here, to run repeatedly:
  actual_Millis = millis();
  Serial.print ("elapsed "), Serial.println(reloj.elapsed()); Serial.println(now());
 if  (flag[0] == 1 || flag[1] == 1 )  {
    reloj.start();
    if (reloj.elapsed()<= 5){
      digitalWrite(redPin, redInt);
      analogWrite(buzPin, intBuzPin);
    }
    else if (reloj.elapsed()> 5 && reloj.elapsed() <= 10) {
      digitalWrite(greenPin, greenInt);
    digitalWrite(redPin, 0);
    analogWrite(buzPin, intBuzPin/6);
    }
   else if (reloj.elapsed()> 10 && reloj.elapsed() <= 15) {
      digitalWrite(bluePin, blueInt);
      digitalWrite(greenPin, 0);
      digitalWrite(redPin, 0);
      analogWrite(buzPin, intBuzPin/2);
    }
     else {
     flag[0] = 0; flag[1] = 0;
      digitalWrite(redPin, 0);
      digitalWrite(bluePin, 0);
      digitalWrite(greenPin, 0);
      analogWrite(buzPin, 0);
      reloj.reset();
      Serial.println ("Alarm2: - off ");
      Serial.println ("Alarm1: - off ");
    }
 }
    Alarm.delay(1000);
  }
  
  void MorningAlarm1() {
    flag[0] = 1;

    Serial.print("Alarm1: - turn lights on. flag = ");  Serial.println(flag[0]);

  }
  void MorningAlarm2() {
    flag[1] = 1;
    Serial.print("Alarm2: - turn lights on. flag = ");  Serial.println(flag[1]);

  }

  
