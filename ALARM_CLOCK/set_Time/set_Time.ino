

/************  This program examines the TimeAlarm library  *******/
//===== Libraries included ======================================
#include <Time.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
#include <LiquidCrystal.h>
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
int alarmMinuto;
int alarmHora;
int alarmSegundo;
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
  flag = 1;
  reloj.start();
}
void lightAndSound() {
  Serial.printf("Alarma %d, %d \n", 0, flag);
  Serial.println ("Pre-oye como va mi ritmo");
  if (reloj.elapsed() <= 5) {
    digitalWrite(redPin, redInt);
    digitalWrite(trecePin, HIGH);
    analogWrite(buzzPin, 127);
    lcd.setCursor(6, 1);
  lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());
  }
  else if (reloj.elapsed() > 5 && reloj.elapsed() <= 6) {
    digitalWrite(redPin, redInt / 2); digitalWrite(greenPin, greenInt / 2);
    digitalWrite(trecePin, LOW);
    analogWrite(buzzPin, 0);
    lcd.setCursor(6, 1);
  lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());
  }
  else if (reloj.elapsed() > 6 && reloj.elapsed() <= 11) {
    digitalWrite(greenPin, greenInt);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 34);
    digitalWrite(trecePin, HIGH);
    lcd.setCursor(6, 1);
  lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());
  }
  else if (reloj.elapsed() > 11 && reloj.elapsed() <= 13) {
    digitalWrite(greenPin, greenInt / 2); digitalWrite(bluePin, blueInt / 2);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 0);
    digitalWrite(trecePin, LOW);
    lcd.setCursor(6, 1);
  lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());
  }
  else if (reloj.elapsed() > 13 && reloj.elapsed() <= 18) {
    digitalWrite(bluePin, greenInt);
    digitalWrite(greenPin, 0);
    analogWrite(buzzPin, 205);
    digitalWrite(trecePin, LOW);
    lcd.setCursor(6, 1);
  lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());
  }

  else if (reloj.elapsed() > 18) {
    Serial.println ("Se acabo, se acabo !");
    reloj.reset();
    flag = 0;
    digitalWrite(trecePin, LOW);
    return;//control returns to main loop.
  }
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
      }
    }
  }
}
//=== function convert strings to nuneric :  ====================
void stringtoNumber(String instruct) {
  int k;
  if (instruct.substring(0, 1) == "1") {
    DD = instruct.substring(1, 3);
    MM = instruct.substring(3, 5);
    AAAA = instruct.substring(5, 9);
    dia = DD.toInt();
    mes = MM.toInt();
    anyo = AAAA.toInt();
    k = 1;
  }
  if (instruct.substring(0, 1) == "2") {
    HH = instruct.substring(1, 3);
    MIN = instruct.substring(3, 5);
    SEG = instruct.substring(5, 7 );
    hora = HH.toInt();
    minuto = MIN.toInt();
    segundo = SEG.toInt();
    k = k + 1;
  }
  if (k == 2) {// Define end of adjustment, setTime and declare Alarms.
    finAjuste = true;
    setTime(hora, minuto, segundo, dia, mes, anyo);
    AlOnce = Alarm.alarmRepeat(12, 0, 5, Alarma);
  }
}
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
//---------------- setup ---------------------------------------------
void setup() {
  while (!Serial);
  Serial.begin(9600);   // Open serial port (9600 bauds).
  //-------- Define pins modes -----------------------
  pinMode(trecePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  //----------- LCD ----------------------------------
  lcd.begin(numCols, numRows);
  lcd.clear();
  lcd.print("Alarma "); // this string is 8characters long
  lcd.setCursor(0, 1);
  lcd.print("Hora: ");
  //----------  Initial screen -----------------------
  printHelp1();
  printHelp2();
  Serial.printf ("hora inicial %d: %d: %d y %d-%d-%d\n", hour(), minute(), second(), day(), month(), year());
}
//---------------- loop ---------------------------------------------

void loop() {
  //----------------  Data Entry (date, time and alarm settings ----------------
  while (finAjuste == false )
  { getEntry(&serialData, &primerNumero);
    stringtoNumber(serialData);
  }
  //----------------  Alarm warning with buzzer an RGB LED --------------------
  if (flag == 1) {
    lightAndSound();
  }
  //------------------ LCD handling ------------------------------------------
  lcd.setCursor(7, 0);//Position the LCD cursor; that is, set the location at which subsequent text written to the LCD will be displayed.
  if (Alarm.getTriggeredAlarmId() != 0) {
    lcd.print("ON");
    Serial.printf("alarmtriggered %d \n", Alarm.getTriggeredAlarmId());
  }
  else {
    lcd.print("OFF");
  }
  
  lcd.setCursor(6, 1);
  lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second());
  //----------------------  Others ----------------------------------------------------
  currentMillis = millis();
  if (currentMillis - previousMillis >= intervalo) // this prevents the time from being constantly shown.
  { previousMillis = currentMillis;
    Serial.printf ("Fecha: %d-%d-%d. Hora: %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
    Serial.printf ("Alarma: %d:%d:%d\n", alarmHora, alarmMinuto,  alarmSegundo);
    Serial.print("flag state "); Serial.println(flag);
  }
  Alarm.delay(1000);

}
