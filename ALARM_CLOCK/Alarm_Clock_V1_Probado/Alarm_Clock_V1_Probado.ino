
//===== Libraries included ======================================
#include <Time.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
#include <LiquidCrystal.h>
/************  This program examines the TimeAlarm library  *******/
//===== Libraries included ======================================
#include <Time.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
#include <LiquidCrystal.h>

//**************** Predsefined constants  *********************
//................  LED(RGB) pins ..............................
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 4;
//..................  Pin 13 .....................................
const int trecePin = 13;
// ...............  buzzer & switchPin ...................................
const int buzzPin = 6;
const int switchPin = 2;
// -----------------  duty cycle --------------------------------
const int redInt = 254;
const int greenInt = 127;
const int blueInt = 254;
//-------------------  time  ---------------------------------
long unsigned intervalo = 1000;
//*****************  selectable variables *********************
//==================== Variables ===============================
//---------------  date & time -------------------------------
int dia;
int mes ;
int anyo;
int hora = 0;
int minuto = 0;
int segundo = 0;
String DD;
String MM;
String AAAA;
String HH = "";
String MIN = "";
String SEG = "";
String hh = "";
String mm = "";
// ---------------- working days alarms -----------------------
int alarmHora;
int alarmMinuto;
const int alarmSegundo = 10;
int k = 0;
// ---------------- weekend alarms ---------------------------
int decalaje;
int alarmHoraWeekEnd ;
int alarmMinutoWeekEnd ;
// -------------   alarms ID ----------------------------------
AlarmId AlMonday;
AlarmId AlTuesday;
AlarmId AlWednesday;
AlarmId AlThursday;
AlarmId AlFriday;
AlarmId AlSaturday;
AlarmId AlSunday;
//------------ alarms state -------------------------------------
int alarmIdState[7];
int volatile alarmEnabled;
//------------------- other time related variables------------------
long unsigned currentMillis;
long unsigned previousMillis;
//------------------ debounce ----------------------------------
long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
//--------------  auxiliary -------------------------------------
char c;
String instruct = "";
String input = "";
int primerNumero = 0;
String respuesta = "";
boolean finAjuste = false;
int flag;
String serialData = "";
//--------------  LCD variables  -------------------
//constants for the number of rows and columns in the LCD
const int numRows = 2;
const int numCols = 16;
int count;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
//-------------  object creation   ------------------------------
StopWatch reloj(StopWatch::SECONDS);
/*

*/
//*******************  FUNCTIONS ****************************************
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
    Serial.println ("oye como va mi ritmo 1");
  }
  else if (reloj.elapsed() > 5 && reloj.elapsed() <= 7 ) {
    digitalWrite(redPin, redInt / 2); digitalWrite(greenPin, greenInt / 2);
    digitalWrite(trecePin, LOW );
    analogWrite(buzzPin, 0);
    Serial.println ("oye como va mi ritmo 2");
    lcd.setCursor(6, 1);
    lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second()); lcd.print("     ");
  }
  else if (reloj.elapsed() > 7 && reloj.elapsed() <= 12 ) {
    digitalWrite(greenPin, greenInt);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 254);
    digitalWrite(trecePin, HIGH);
    Serial.println ("oye como va mi ritmo 3");
    lcd.setCursor(6, 1);
    lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second()); lcd.print("     ");

  }
  else if (reloj.elapsed() > 12 && reloj.elapsed() <= 15 ) {
    digitalWrite(greenPin, greenInt / 2); digitalWrite(bluePin, blueInt / 2);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 189);
    digitalWrite(trecePin,  LOW);
    Serial.println ("oye como va mi ritmo 4");
    lcd.setCursor(6, 1);
    lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second()); lcd.print("     ");
  }
  else if (reloj.elapsed() > 15) {
    digitalWrite(trecePin, LOW);
    digitalWrite(greenPin, 0);
    digitalWrite(bluePin, 0);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 0);
    Serial.println ("Se acabo, se acabo !");
    reloj.reset();
    flag = 0;
    return;//control returns to main loop.
  }
}

//=== function1 to print the command list:  ===========================
void printHelp1() {
  Serial.println ("Instrucciones para ajustes del calendario");
  Serial.println ("Calendario: Introduzca el digito '1' y luego en orden y con los digitos indicados");
  Serial.print ("dia: DD, mes: MM, anyo: AAAA\t");
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
  Serial.print ("4. Hora: Introduzca el digito '4' y luego las horas de decalaje respecto a laborable.\t");
  Serial.println ("Termine con un '/' ");
}

//=== function to collect data throgh serial monitor:  ==================
void getEntry(String * devol1, int *devol2) {
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
          Serial.print("alarma dia laborable: "); Serial.println(salida.substring(1, 3) + ":" + salida.substring(3, 5) + ":" + alarmSegundo);
          Serial.flush();
          break;
        case 4 :
          Serial.print("alarma week end: decalaje "); Serial.println(salida.substring(1, 3) + "h:" +  alarmHoraWeekEnd + "m:" + alarmMinutoWeekEnd);
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
    k = 1;

  }
  if (instruct.substring(0, 1) == "2") {
    HH = instruct.substring(1, 3);
    MIN = instruct.substring(3, 5);
    SEG = instruct.substring(5, 7 );
    hora = HH.toInt();
    minuto = MIN.toInt();
    segundo = SEG.toInt();
    k = 2;
    setTime(hora, minuto, segundo, dia, mes, anyo);
  }
  if (instruct.substring(0, 1) == "3") {
    hh = instruct.substring(1, 3);
    mm = instruct.substring(3, 5);
    alarmHora = hh.toInt();
    alarmMinuto = mm.toInt();
    k = 3;
    AlMonday =  Alarm.alarmRepeat(dowMonday, alarmHora, alarmMinuto, alarmSegundo, Alarma);
    AlTuesday =  Alarm.alarmRepeat(dowTuesday, alarmHora, alarmMinuto, alarmSegundo, Alarma);
    AlWednesday =  Alarm.alarmRepeat(dowWednesday, alarmHora, alarmMinuto, alarmSegundo, Alarma);
    AlThursday =  Alarm.alarmRepeat(dowThursday, alarmHora, alarmMinuto, alarmSegundo, Alarma);
    AlFriday = Alarm.alarmRepeat(dowFriday, alarmHora, alarmMinuto, alarmSegundo, Alarma);

  }
  if (instruct.substring(0, 1) == "4") {
    String decala = instruct.substring(1, 2);
    decalaje = decala.toInt();
    alarmMinutoWeekEnd == alarmHora + decalaje;
alarmMinutoWeekEnd: alarmMinuto;
    AlSaturday = Alarm.alarmRepeat(dowSaturday, alarmHora, alarmMinuto, alarmSegundo, Alarma);
    AlSunday = Alarm.alarmRepeat(dowSunday, alarmHora, alarmMinuto, alarmSegundo, Alarma);
    k = 4;
  }
  if (k == 4) {// Define end of adjustment, setTime and declare Alarms.
    finAjuste = true;
  }

}

//========================   Install the interrupt routines ======================================.
//---------------------------  debounce ---------------------------------------------------------
void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    ServicioBoton();
    last_micros = micros();
  }
}
//----------------------- interrupt service -------------------------------------------------
void ServicioBoton() {
  int alarmStateAnt=alarmEnabled;
  int flagAnt=flag;
  
  digitalWrite(trecePin, LOW);
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 0);
  digitalWrite(redPin, 0);
  analogWrite(buzzPin, 0);
  Serial.println ("Se acabo, se acabo !");
  Serial.printf("Service boton\n"); Serial.printf("alarmEnabled:   %d\n", alarmEnabled);
  if ( alarmStateAnt == 1 && flagAnt==0) {
    for (int i; i < 7; ++i) {
      Alarm.disable(i);
      alarmIdState[i] = 0;
    }
    // reloj.stop();
    alarmEnabled = 0;
    return;
  } 
  else if ( alarmStateAnt == 0 && flagAnt==0) {
    for (int i; i < 7; ++i) {
      Alarm.enable(i);
      alarmIdState[i] = 1;
    }
    //reloj.stop();
    alarmEnabled=1;
    return;
  }
   else if ( alarmStateAnt == 0 && flagAnt==1){
    for (int i; i < 7; ++i) {
      Alarm.enable(i);
      alarmIdState[i] = 1;
    }
    //reloj.stop();
    alarmEnabled=1;
    return;
    }
    else if ( alarmStateAnt == 1 && flagAnt==0){
    for (int i; i < 7; ++i) {
      Alarm.enable(i);
      alarmIdState[i] = 0;
    }
    //reloj.stop();
    flag = flagAnt;
    alarmEnabled=0;
    return;
    }
    else if ( alarmStateAnt == 1 && flagAnt==1) {
    for (int i; i < 7; ++i) {
      Alarm.disable(i);
      alarmIdState[i] = 0;
    }
    //reloj.stop();
     alarmEnabled=0;
     return;
  }
    else {
      return;}
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
  digitalWrite(trecePin, LOW);
  digitalWrite(greenPin, 0);
  digitalWrite(redPin, 0);
  digitalWrite(bluePin, 0);
  //----------- LCD ----------------------------------

  attachInterrupt( digitalPinToInterrupt(switchPin), ServicioBoton, RISING);
  alarmEnabled=1;
  //----------- Enable all alarms ------------------------
  for (int i; i < 7; ++i) {
    Alarm.enable(i);
    alarmIdState[i] = 1;
    alarmEnabled = alarmEnabled * alarmIdState[i];
    Serial.printf ("alarmIdState[i]=%d\n", alarmIdState[i]);
  }
  lcd.begin(numCols, numRows);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarma: ");
    lcd.setCursor(7, 0);
    lcd.print("ON"); lcd.print("     ");
   // this string is 8characters long
  lcd.setCursor(0, 1);
  lcd.print("Hora: ");


  //----------  Initial screen -----------------------
  printHelp1();
  printHelp2();
  printHelp3();
  printHelp4();
  Serial.printf ("hora inicial %d: %d: %d y %d-%d-%d\n", hour(), minute(), second(), day(), month(), year());
   Serial.printf ("alarmEnabled %d\n", alarmEnabled);
  pinMode(switchPin, INPUT_PULLUP);
  }
//---------------- loop ---------------------------------------------

void loop() {
  //----------------  Data Entry (date, time and alarm settings ----------------
  while (finAjuste == false )
  { getEntry(&serialData, &primerNumero);
    stringtoNumber(serialData);
  }
  //----------------  Alarm warning with buzzer an RGB LED --------------------
  if (flag == 1 && alarmEnabled == 1) {
    lightAndSound();
    Serial.printf ("Fecha light & sound: %d-%d-%d. Hora: %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
    Serial.print("flag state "); Serial.println(flag);
  }

  //----------------------  Others ----------------------------------------------------
  currentMillis = millis();
  if (currentMillis - previousMillis >= intervalo) // this prevents the time from being constantly shown.
  { previousMillis = currentMillis;
    Serial.printf ("Fecha: %d-%d-%d. Hora: %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
    Serial.printf ("Alarma: %d:%d:%d\n", alarmHora, alarmMinuto,  alarmSegundo);
    Serial.print("flag state "); Serial.println(flag);
    if (alarmEnabled == 1) {
      lcd.setCursor(7, 0);
      lcd.print("ON"); lcd.print("     ");
    }
    else {
      lcd.setCursor(7, 0);
      lcd.print("OFF"); lcd.print("    ");
    }
    lcd.setCursor(6, 1);
    lcd.print(hour()); lcd.print(":"); lcd.print(minute()); lcd.print(":"); lcd.print(second()); lcd.print("     ");

  }
  Alarm.delay(0);

}
