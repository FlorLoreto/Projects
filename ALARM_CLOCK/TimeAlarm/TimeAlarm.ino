/************  This program examines the TimeAlarm library  *******/
//===== Libraries included ======================================
#include <Time.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
//==================== Variables ===============================
//---------------  date & alarms -------------------------------
int dia = 18;
int mes = 4;
int anyo = 2016;
int hora = 0;
int minuto = 0;
int segundo = 0;
// ---------------- working days alarms -----------------------
int alarmMinuto = 0;
int alarmHora = 0;
int alarmSegundo = 5;
int alarmHoraWeekEnd=alarmHora+3;
int alarmMinutoWeekEnd = alarmMinuto;
// -------------   alarms ID ----------------------------------
AlarmId AlMonday;
AlarmId AlMonday2;
AlarmId AlTuesday;
AlarmId AlWednesday;
AlarmId AlThursday;
AlarmId AlFriday;
AlarmId AlSaturday;
AlarmId AlSunday;
//------------------- other ------------------
int flag[7] = {0, 0, 0, 0, 0, 0, 0};
long unsigned currentMillis;
long unsigned previousMillis;
long unsigned intervalo;
// ---------------  pin definition -------------------------------
// ................. pin 13 .....................................
const int trecePin = 13;
//--------------  object creation   ------------------------------
StopWatch reloj(StopWatch::SECONDS);

//=== function alarm Service : ===========================================
void Alarma0() {
  flag[0] = 1;
  reloj.start();
}
void Alarma1() {
  flag[1] = 1;
  reloj.start();
}
void Alarma2() {
  flag[2] = 1;
  reloj.start();
}
void Alarma3() {
  flag[3] = 1;
  reloj.start();
}
void Alarma4() {
  flag[4] = 1;
  reloj.start();
}
void Alarma5() {
  flag[5] = 1;
  reloj.start();
}
void Alarma6() {
  flag[6] = 1;
  reloj.start();
}
void lightAndSound() {
 
  if (reloj.elapsed() <= 5) {
    digitalWrite(trecePin, HIGH);
  }
  else if (reloj.elapsed() > 5 && reloj.elapsed() <= 6) {
    digitalWrite(trecePin, LOW);
  }
  else if (reloj.elapsed() > 6 && reloj.elapsed() <= 11) {
    digitalWrite(trecePin, HIGH);
  }
  else if (reloj.elapsed() > 11 && reloj.elapsed() <= 13) {
    digitalWrite(trecePin, LOW);
  }
  else if (reloj.elapsed() > 13 && reloj.elapsed() <= 18) {
    digitalWrite(trecePin, HIGH);
  }
  else {
    digitalWrite(trecePin, LOW);
    for (int i;i<7;++i){
    flag[i] = 0;
    }
    reloj.reset();
  }
}


//---------------- setup ---------------------------------------------
void setup() {
  setTime(0, 0, 0, 19, 04, 2016);
  Serial.begin(9600);   // Open serial port (9600 bauds).
  pinMode(13, OUTPUT);
  digitalWrite(trecePin, 0);
  setTime(hora, minuto, segundo, dia, mes, anyo);
 AlMonday = Alarm.alarmRepeat(dowMonday, alarmHora, alarmMinuto,  alarmSegundo, Alarma0);
 AlTuesday = Alarm.alarmRepeat(dowTuesday, alarmHora, alarmMinuto,  alarmSegundo, Alarma1);
 AlWednesday = Alarm.alarmRepeat(dowWednesday, alarmHora, alarmMinuto,  alarmSegundo, Alarma2);
 AlThursday = Alarm.alarmRepeat(dowThursday, alarmHora, alarmMinuto,  alarmSegundo, Alarma3);
 AlFriday = Alarm.alarmRepeat(dowFriday, alarmHora, alarmMinuto,  alarmSegundo, Alarma4);
 AlSaturday = Alarm.alarmRepeat(dowSaturday, alarmHoraWeekEnd, alarmMinutoWeekEnd,  alarmSegundo, Alarma5);
 AlSunday = Alarm.alarmRepeat(dowSunday, alarmHoraWeekEnd, alarmMinutoWeekEnd,  alarmSegundo, Alarma6);
 Serial.print ("fecha seteada "); Serial.printf ("%d:%d:%d \t%d-%d-%d.\n", hora, minuto, segundo, dia, mes, anyo);
 Serial.print ("valores de AlarmId \n"); Serial.print ("AlMonday"); Serial.println (AlMonday);  Serial.print ("AlMonday2"); Serial.println (AlMonday2);
 Serial.print ("AlTuesday");  Serial.println (AlTuesday); Serial.print ("AlWednesday"); Serial.println (AlWednesday); 
 Serial.print ("AlThursday"); Serial.println (AlThursday);  Serial.print ("AlFriday"); Serial.println (AlFriday);  
 Serial.print ("AlSaturday"); Serial.println (AlSaturday);  Serial.print ("AlSunday"); Serial.println (AlSunday);
 
}
//---------------- loop ---------------------------------------------

void loop() {
 
  currentMillis = millis();
  if (flag[0] == 1) {
    lightAndSound() ;
  }
  if (currentMillis - previousMillis >= intervalo) // this prevents the time from being constantly shown.
  { previousMillis = currentMillis;
    Serial.printf ("Fecha: %d-%d-%d. Hora: %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
    Serial.printf ("Alarma: %d:%d:%d\n", alarmHora, alarmMinuto,  alarmSegundo);
  }
  else {
    Serial.print("");
    reloj.reset();
    digitalWrite(trecePin, LOW);
  }


  Alarm.delay(1000);

}
