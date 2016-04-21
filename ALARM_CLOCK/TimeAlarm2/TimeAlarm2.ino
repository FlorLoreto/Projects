/************  This program examines the TimeAlarm library  *******/
//===== Libraries included ======================================
#include <Time.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
//==================== Variables ===============================
//---------------  date & alarms -------------------------------
int dia = 20;
int mes = 4;
int anyo = 2016;
int hora = 0;
int minuto = 0;
int segundo = 0;
// .............. auxiliary variables .........................
String DD;
String MM;
String AAAA;
String HH = "";
String MIN = "";
String SEG = "";
String hh = "";
String mm = "";
// ---------------- working days alarms -----------------------
int alarmMinuto;
int alarmHora;
int alarmSegundo;
int alarmHoraWeekEnd = alarmHora + 3;
int alarmMinutoWeekEnd = alarmMinuto;
const int trecePin = 13;
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
/*AlarmId AlMonday;
  AlarmId AlMonday2;
  AlarmId AlTuesday;
  AlarmId AlWednesday;
  AlarmId AlThursday;
  AlarmId AlFriday;
  AlarmId AlSaturday;
  AlarmId AlSunday;*/
AlarmId AlOnce;
//------------------- other ------------------
int flag[7] = {0, 0, 0, 0, 0, 0, 0};
long unsigned currentMillis;
long unsigned previousMillis;
long unsigned intervalo;
int decalaje;
// ---------------  pin definition -------------------------------
char c;
String instruct = "";
String input = "";
int primerNumero = 0;
String serialData = "";
String respuesta = "";
boolean finAjuste = false;
//-------------  object creation   ------------------------------
StopWatch reloj(StopWatch::SECONDS);

//=== function alarm Service : ===========================================
void Alarma0() {
  flag[0] = 1;
  reloj.start();
  Serial.printf("Alarma %d, %d\n", 0, flag[0]);
}
void Alarma1() {
  flag[1] = 1;
  reloj.start();
  Serial.printf("Alarma %d, %d\n", 1, flag[1]);
}
void Alarma2() {
  flag[2] = 1;
  reloj.start();
  Serial.printf("Alarma %d, %d\n", 2, flag[2]);
}
void Alarma3() {
  flag[3] = 1;
  reloj.start();
  Serial.printf("Alarma %d, %d\n", 3, flag[3]);
}
void Alarma4() {
  flag[4] = 1;
  reloj.start();
  Serial.printf("Alarma %d, %d\n", 4, flag[4]);
}
void Alarma5() {
  flag[5] = 1;
  reloj.start();
  Serial.printf("Alarma %d, %d\n", 5, flag[5]);
}
void Alarma6() {
  flag[6] = 1;
  reloj.start();
  Serial.printf("Alarma %d, %d\n", 6, flag[6]);
}
/*void lightAndSound() {

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
  }*/
void lightAndSound() {
  if (reloj.elapsed() <= 5) {
    digitalWrite(redPin, redInt);
    digitalWrite(trecePin, HIGH);
    analogWrite(buzzPin, 127);
  }
  else if (reloj.elapsed() > 5 && reloj.elapsed() <= 6) {
    digitalWrite(redPin, redInt / 2); digitalWrite(greenPin, greenInt / 2);
    digitalWrite(trecePin, LOW);
    analogWrite(buzzPin, 0);
  }
  else if (reloj.elapsed() > 6 && reloj.elapsed() <= 11) {
    digitalWrite(greenPin, greenInt);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 34);
    digitalWrite(trecePin, HIGH);
  }
  else if (reloj.elapsed() > 11 && reloj.elapsed() <= 13) {
    digitalWrite(greenPin, greenInt / 2); digitalWrite(bluePin, blueInt / 2);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 0);
    digitalWrite(trecePin, LOW);
  }
  else if (reloj.elapsed() > 13 && reloj.elapsed() <= 18) {
    digitalWrite(bluePin, greenInt);
    digitalWrite(greenPin, 0);
    analogWrite(buzzPin, 205);
    digitalWrite(trecePin, LOW);
  }
  else {
    digitalWrite(greenPin, 0);
    digitalWrite(bluePin, 0);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 0);
    for (int i; i < 7; ++i) {
      flag[i] = 0;
    }
    reloj.reset();
  }
}

void printHelp1() {
  Serial.println ("Instrucciones para ajustes del calendario");
  Serial.println ("Calendario: Introduzca el digito '1' y luego en orden y con dos digitos");
  Serial.print ("dia: DD, mes: MM, anyo: AA\t");
  Serial.println ("Termine con un '/' ");
}
//=== function2 to print the command list:  ===========================
void printHelp2() {
  Serial.println ("Instrucciones para ajustes del reloj");
  Serial.print ("2. Hora: Introduzca el digito '2' y luego en orden la hora: HH , minutos: MM y segundos: SS\t");
  Serial.println ("Termine con un '/' ");
}
//=== function to collect data throgh serial monitor:  ==================
void getEntry(String *devol1, int *devol2) {
  String salida = "";
  // Read any serial input
  while (Serial.available() > 0)
  {
    c = (char) Serial.read();
    Serial.print("input caracter "); Serial.println(c);
    input = input + c; // Read in one char at a time
    //Serial.print("inputagregado "); Serial.println(input);
    // Serial.print("longitud "); Serial.println(input.length());
    //Serial.print("Ultimo character "); Serial.println(input[input.length() - 1]);
    if (input[input.length() - 1] == '/') {
      salida = input.substring(0, input.length() - 1);
      Serial.print("input de salida "); Serial.println(salida);
      input = "";
      *devol1 = salida;
      *devol2 = salida[0] - '0';
      Serial.printf("tipo datos   %d, %d\n", *devol2, salida[0]);
      switch (*devol2) {
        case 1 :
          Serial.print("datos de fecha: "); Serial.println(salida.substring(1, 3) + "-" + salida.substring(3, 5) + "-" + salida.substring(5, 9));
          Serial.flush();
          break;
        case 2 :
          Serial.print("datos de hora: "); Serial.println(salida.substring(1, 3) + ":" + salida.substring(3, 5) + ":" + salida.substring(5, 7));
          Serial.flush();
          finAjuste = true;
          break;
      }
    }
  }
}
//=== function convert strings to nuneric :  ====================
void stringtoNumber(String instruct) {
  if (instruct.substring(0, 1) == "1") {
    DD = instruct.substring(1, 3);
    MM = instruct.substring(3, 5);
    AAAA = instruct.substring(5, 9);
    dia = DD.toInt();
    mes = MM.toInt();
    anyo = AAAA.toInt();

  }
  if (instruct.substring(0, 1) == "2") {
    HH = instruct.substring(1, 3);
    MIN = instruct.substring(3, 5);
    SEG = instruct.substring(5, 7 );
    hora = HH.toInt();
    minuto = MIN.toInt();
    segundo = SEG.toInt();

  }
  if (instruct.substring(0, 1) == "3") {
    hh = instruct.substring(1, 3);
    mm = instruct.substring(3, 5);
    alarmHora = hh.toInt();
    alarmMinuto = mm.toInt();
  }
  if (instruct.substring(0, 1) == "4") {
    String decala = instruct.substring(1, 2);
    decalaje = decala.toInt();
  }
}

//---------------- setup ---------------------------------------------
void setup() {
  while (!Serial);
  Serial.begin(9600);   // Open serial port (9600 bauds).
  pinMode(trecePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  digitalWrite(trecePin, 0);
  AlOnce = Alarm.alarmOnce(12, 0,  5, Alarma0);
  printHelp1();
  printHelp2();
  /* AlMonday =(dowMonday, alarmHora, alarmMinuto,  alarmSegundo, Alarma0);
    AlTuesday = Alarm.alarmRepeat(dowTuesday, alarmHora, alarmMinuto,  alarmSegundo, Alarma1);
    AlWednesday = Alarm.alarmRepeat(dowWednesday, alarmHora, alarmMinuto,  alarmSegundo, Alarma2);
    AlThursday = Alarm.alarmRepeat(dowThursday, alarmHora, alarmMinuto,  alarmSegundo, Alarma3);
    AlFriday = Alarm.alarmRepeat(dowFriday, alarmHora, alarmMinuto,  alarmSegundo, Alarma4);
    AlSaturday = Alarm.alarmRepeat(dowSaturday, alarmHoraWeekEnd, alarmMinutoWeekEnd,  alarmSegundo, Alarma5);
    AlSunday = Alarm.alarmRepeat(dowSunday, alarmHoraWeekEnd, alarmMinutoWeekEnd,  alarmSegundo, Alarma6);
    Serial.print ("fecha seteada "); Serial.printf ("%d:%d:%d \t%d-%d-%d.\n", hora, minuto, segundo, dia, mes, anyo);*/
  /* Serial.print ("valores de AlarmId \n"); Serial.print ("AlMonday"); Serial.println (AlMonday);  Serial.print ("AlMonday2"); Serial.println (AlMonday2);
    Serial.print ("AlTuesday");  Serial.println (AlTuesday); Serial.print ("AlWednesday"); Serial.println (AlWednesday);
    Serial.print ("AlThursday"); Serial.println (AlThursday);  Serial.print ("AlFriday"); Serial.println (AlFriday);
    Serial.print ("AlSaturday"); Serial.println (AlSaturday);  Serial.print ("AlSunday"); Serial.println (AlSunday);*/

}
//---------------- loop ---------------------------------------------

void loop() {
  while ((Serial.available()) && finAjuste == false)
  {
    getEntry(&serialData, &primerNumero);
    stringtoNumber(serialData);
    setTime(hora, minuto, segundo, dia, mes, anyo);
    alarmMinuto = minuto;
    alarmHora = hora;
    alarmSegundo = segundo + 5;
  }

  currentMillis = millis();
  if ((flag[0] == 1) || (flag[1] == 1) || (flag[2] == 1) || (flag[3] == 1) || (flag[4] == 1) || (flag[5] == 1) || (flag[6] == 1)) {
    lightAndSound() ;
  }
  if (currentMillis - previousMillis >= intervalo && finAjuste == true) // this prevents the time from being constantly shown.
  { previousMillis = currentMillis;
    Serial.printf ("Fecha: %d-%d-%d. Hora: %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
    Serial.printf ("Alarma: %d:%d:%d\n", alarmHora, alarmMinuto,  alarmSegundo);
  }
  else {
    Serial.print("");
    reloj.reset();
    digitalWrite(trecePin, LOW);
  }


  Alarm.delay(0);

}
