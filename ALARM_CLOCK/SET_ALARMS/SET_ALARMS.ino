/* DATE: 18-04-2016
************  This program sets the calendar, time and alarms  ***********
  No NEW LINE IN Serial Monitor */
//===== Libraries included ======================================
#include <Time.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
//==================== Variables ===============================
//---------------  date & alarms -------------------------------
int dia = 0;
int mes = 0;
int anyo = 0;
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
// ---------------- working days alarms -----------------------
int alarmMinuto = 0;
int alarmHora = 0;
int alarmSegundo = 5;
// .............. auxiliary variables .........................
String hh = "";
String mm = "";
// ---------------  weekend alarms ---------------------------
int alarmHoraWeekEnd;
int alarmMinutoWeekEnd;
// ++++++++++++++++ auxiliary variable ************************
String input = "";
// -------------   alarms ID ----------------------------------
AlarmId AlMonday;
AlarmId AlTuesday;
AlarmId AlWednesday;
AlarmId AlThursday;
AlarmId AlFriday;
AlarmId AlSaturday;
AlarmId AlSunday;
//--------------  auxiliary -------------------------------------
char c;
String instruct = "";
int primerNumero = 0;
String serialData = "";
unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long intervalo = 1000;
String respuesta = "";
int flag[7];
// ---------------  pin definition -------------------------------
// ................. pin 13 .....................................
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
// --------------------- other variables -------------------------
int k = 0;
int kD = 0;
//--------------  object creation   ------------------------------
StopWatch reloj(StopWatch::SECONDS);
//=== function1 to print the command list:  ===========================
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
//=== function3 to print the command list:  ===========================
void printHelp3() {
  Serial.println ("Instrucciones para ajustes de la alarma dia laborable");
  Serial.print ("3. Hora: Introduzca el digito '3' y luego en orden la hora: HH y minutos: MM\t");
  Serial.println ("Termine con un '/' ");
}
//=== function4 to print the command list:  ===========================
void printHelp4() {
  Serial.println ("Instrucciones para ajustes de la alarma fin de semana");
  Serial.print ("4. Hora: Introduzca el dígito '4' y luego en orden la hora: HH y minutos: MM\t");
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
          break;
        case 3 :
          Serial.print ("datos de alarma laborable: "); Serial.println(salida.substring(1, 3) + ":" + salida.substring(3, 5));
          Serial.flush();
          break;
        case 4 :
          Serial.print ("datos de alarma fin de semana: "); Serial.println(salida.substring(1, 3) + ":" + salida.substring(3, 5));
          Serial.flush();
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
    hh = instruct.substring(1, 3);
    mm = instruct.substring(3, 5);
    alarmHoraWeekEnd = hh.toInt();
    alarmMinutoWeekEnd = mm.toInt();
  }
}

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
    digitalWrite(redPin, redInt);
    digitalWrite(trecePin, HIGH);
    analogWrite(buzzPin, 127);
  }
  else if (reloj.elapsed() > 5 && k <= reloj.elapsed()) {
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
    for (int i;i<7;++i){
    flag[i] = 0;
    }
    reloj.reset();
      }
}


//---------------- setup ---------------------------------------------
void setup() {
  while (!Serial);
  setTime(0, 0, 0, 1, 1, 1970);
  Serial.begin(9600);   // Open serial port (9600 bauds).
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  digitalWrite(redPin, 0);
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 0);
 AlMonday = Alarm.alarmRepeat(dowMonday, alarmHora, alarmMinuto,  alarmSegundo, Alarma0);
 AlTuesday = Alarm.alarmRepeat(dowTuesday, alarmHora, alarmMinuto,  alarmSegundo, Alarma1);
 AlWednesday = Alarm.alarmRepeat(dowWednesday, alarmHora, alarmMinuto,  alarmSegundo, Alarma2);
 AlThursday = Alarm.alarmRepeat(dowThursday, alarmHora, alarmMinuto,  alarmSegundo, Alarma3);
 AlFriday = Alarm.alarmRepeat(dowFriday, alarmHora, alarmMinuto,  alarmSegundo, Alarma4);
 AlSaturday = Alarm.alarmRepeat(dowSaturday, alarmHoraWeekEnd, alarmMinutoWeekEnd,  alarmSegundo, Alarma5);
 AlSunday = Alarm.alarmRepeat(dowSunday, alarmHoraWeekEnd, alarmMinutoWeekEnd,  alarmSegundo, Alarma6);
  printHelp1();          // Print the command list.
  Serial.print ("fecha inicial "); Serial.printf ("%d-%d-%d.\n", day(), month(), year());
  printHelp2();
  Serial.print ("hora inicial "); Serial.printf ("%d:%d:%d.\n", hour(), minute(), second());
  printHelp3();
  Serial.print ("alarma laborable inicial "); Serial.printf ("%d:%d:%d.\n", 0, 0, 0);
  printHelp4();
  Serial.print ("alarma fin de semana inicial "); Serial.printf ("%d:%d:%d.\n", 0, 0, 0);
}
//---------------- loop ---------------------------------------------

void loop() {
  currentMillis = millis();

  while ((Serial.available()) && (dia == 0 && mes == 0 && anyo == 0) || (hora == 0 && minuto == 0 && segundo == 0) || (alarmHora == 0 && alarmMinuto == 0) || (alarmHoraWeekEnd == 0 && alarmMinutoWeekEnd == 0)) {
    getEntry(&serialData, &primerNumero);
    stringtoNumber(serialData);
      
    setTime(hora, minuto, segundo, dia, mes, anyo);
       }

 
  if (currentMillis - previousMillis >= intervalo ) // this prevents the time from being constantly shown.
  { previousMillis = currentMillis;
    Serial.print ("\nserialData\t"); Serial.println (serialData);
    Serial.printf ("Fecha: %d-%d-%d. Hora: %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
    Serial.printf ("Alarma diaria: %d:%d:%d\n", alarmHora, alarmMinuto, 10);
     }
  else {
    Serial.print("");
  }
  if (flag[0] == 1||flag[1] == 1||flag[2] == 1||flag[3] == 1||flag[4] == 1||flag[5] == 1||flag[6] == 1) {
    lightAndSound();
  }

  Alarm.delay(0);
}
