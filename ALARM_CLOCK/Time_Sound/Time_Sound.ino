

/************  This program examines the TimeAlarm library  *******/
//===== Libraries included ======================================
#include <Time.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
#include <LiquidCrystal.h>
#include <elapsedMillis.h>
//==================== Variables ===============================
//---------------  date & alarms -------------------------------
int dia;
int mes ;
int anyo;
int hora = 0;
int minuto = 0;
int segundo = 0;
int flag;
// ---------------- working days alarms -----------------------
int alarmMinuto=0;
int alarmHora=12;
int alarmSegundo=5;
int alarmHoraWeekEnd;
int alarmMinutoWeekEnd;
const int trecePin = 13;
String DD;
String MM;
String AAAA;
String HH = "";
String MIN = "";
String SEG = "";
String hh = "";
String mm = "";
String serialData = "";
//................  LEG (RGB) pins ..............................
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 4;
// ...............  buzzer pin ...................................
const int buzzPin = 6;
// -----------------  duty cycle --------------------------------
const int redInt = 254;
const int greenInt = 254;
const int blueInt = 254;
// -------------   alarms ID ----------------------------------
AlarmId AlOnce;
AlarmId AlMonday;
AlarmId AlMonday2;
AlarmId AlTuesday;
AlarmId AlWednesday;
AlarmId AlThursday;
AlarmId AlFriday;
AlarmId AlSaturday;
AlarmId AlSunday;
//------------------- other ------------------
long unsigned currentMillis;
long unsigned previousMillis;
long unsigned intervalo = 1000;
long unsigned tPass;
//--------------  auxiliary -------------------------------------
char c;
String instruct = "";
String input = "";
int primerNumero = 0;
String respuesta = "";
boolean finAjuste = false;
//--------------  LCD variables  and objects -------------------
//constants for the number of rows and columns in the LCD
const int numRows = 2;
const int numCols = 16;
int count;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
//-------------  object creation   ------------------------------
StopWatch reloj(StopWatch::SECONDS);

//=== function alarm Service : ===========================================
void Alarma() {
    lcd.setCursor(6, 1);
    lcd.print(alarmHora); lcd.print(":"); lcd.print(alarmMinuto); lcd.print(":"); lcd.print(alarmSegundo);lcd.print("     ");
  flag = 1;
  reloj.start();
  
}
void lightAndSound() {
  Serial.printf("Alarma %d, %d \n", 0, flag);
  Serial.println ("Pre-oye como va mi ritmo");
  Serial.printf ("Se ve la hora %d?", hour());
  
  lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second()-1);lcd.print("     ");

  if (reloj.elapsed() <= 4) {
    
    digitalWrite(redPin, redInt);
    digitalWrite(trecePin, HIGH);
    analogWrite(buzzPin, 127);
    if (reloj.elapsed() > 0 && reloj.elapsed() < 1 ) {
     
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
      if (reloj.elapsed() > 1 && reloj.elapsed() < 2) {
        
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
    else if (reloj.elapsed() > 2 && reloj.elapsed() < 3) {
     
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
    else if (reloj.elapsed() > 3 && reloj.elapsed() < 4) {
     
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
  }
  else if (reloj.elapsed() > 4 && reloj.elapsed() <= 8) {
  
    digitalWrite(redPin, redInt / 2); digitalWrite(greenPin, greenInt / 2);
    digitalWrite(trecePin, LOW);
    analogWrite(buzzPin, 60);
    if (reloj.elapsed() > 4 && reloj.elapsed() < 5) {
      
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
    else if (reloj.elapsed() > 5 && reloj.elapsed() < 6) {
      
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
    else if (reloj.elapsed() > 6 && reloj.elapsed() < 7) {
     
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
    else if (reloj.elapsed() > 7 && reloj.elapsed() < 8) {
      
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }

  }
  else if (reloj.elapsed() > 8 && reloj.elapsed() <= 12) {
    
    digitalWrite(greenPin, greenInt);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 33);
    digitalWrite(trecePin, HIGH);
    currentMillis = millis();
    if (reloj.elapsed() > 9) {
     
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
    else if (reloj.elapsed() > 10) {
   
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
    else if (reloj.elapsed() > 11) {
     
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
  }
  else if (reloj.elapsed() > 12 && reloj.elapsed() <= 16) {
  
    digitalWrite(greenPin, greenInt / 2); digitalWrite(bluePin, blueInt / 2);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 0);
    digitalWrite(trecePin, LOW);
    if (reloj.elapsed() > 12) {
      
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
    else if (reloj.elapsed() > 13) {
     
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
    else if (reloj.elapsed() > 14) {
      
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
    else if (reloj.elapsed() > 15) {
      
      lcd.setCursor(6, 1);
      lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
    }
  }
  else if (reloj.elapsed() > 16) {
    
    Serial.println ("Se acabo, se acabo !");
    reloj.reset();
    flag = 0;
    digitalWrite(trecePin, LOW);
    return;//control returns to main loop.
  }
}
//---------------- LCD clean --------------------------------------
void liquidClean(){
  lcd.begin(numCols, numRows);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarma "); // this string is 8characters long
  lcd.setCursor(0, 1);
  lcd.print("Hora: ");
  }
//---------------- setup ---------------------------------------------
void setup() {
  while (!Serial);
  Serial.begin(9600);   // Open serial port (9600 bauds).
  //-------- Define pins modes -----------------------
  pinMode(trecePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  //----------- LCD ----------------------------------
  lcd.begin(numCols, numRows);
 lcd.clear();
  lcd.print("Alarma "); // this string is 8characters long
 lcd.setCursor(0, 1);
  lcd.print("Hora: ");
  //----------  Initial screen -----------------------
  setTime(12, 00, 00, 22, 4, 2016);
  Serial.printf ("hora inicial %d: %d: %d y %d-%d-%d\n", hour(), minute(), second(), day(), month(), year());
  AlOnce = Alarm.alarmRepeat(alarmHora, alarmMinuto, alarmSegundo, Alarma);
  for (int i = A0; i < A6; ++i) {
    digitalWrite(A0, HIGH);
  }

  pinMode(7, INPUT_PULLUP);
  

}
//---------------- loop ---------------------------------------------

void loop() {
  //----------------  Alarm warning with buzzer an RGB LED --------------------
   //----------------------  Others ----------------------------------------------------
  currentMillis = millis();
  if (currentMillis - previousMillis >= intervalo) // this prevents the time from being constantly shown.
  { previousMillis = currentMillis;
    Serial.printf ("Fecha: %d-%d-%d. Hora: %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
    Serial.printf ("Alarma: %d:%d:%d\n", alarmHora, alarmMinuto,  alarmSegundo);
    Serial.print("flag state "); Serial.println(flag);
    liquidClean();
    lcd.setCursor(6, 1);
    lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());lcd.print("     ");
  }
  if (flag == 1) {
    lightAndSound();

  } else {
    digitalWrite(trecePin, LOW);
    digitalWrite(greenPin, 0);
    digitalWrite(redPin, 0);
    digitalWrite(bluePin, 0);
    analogWrite(buzzPin, 0);
    
  }
  //------------------ LCD handling ------------------------------------------
  lcd.setCursor(7, 0);//Position the LCD cursor; that is, set the location at which subsequent text written to the LCD will be displayed.
  if (Alarm.getTriggeredAlarmId() == AlOnce) {
    lcd.print("ON"); lcd.print(" ");
    Serial.printf("alarmtriggered %d \n", Alarm.getTriggeredAlarmId());
  }
  else {
    lcd.setCursor(7, 0);
    lcd.print("OFF");
  }

  /*lcd.setCursor(6, 1);
    lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());*/
 
  Alarm.delay(0);

}

