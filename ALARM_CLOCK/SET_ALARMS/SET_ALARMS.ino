/* DATE: 06-04-2016
************  This program sets the calendar, time and alarms ************/
//===== Libraries included ======================================
#include <Time.h>
#include <TimeAlarms.h>
#include <avr/wdt.h>
#include <TimerOne.h>
#include <StopWatch.h>
//=====  Variables ==============================================
//---------------  date & alarms -------------------------------
int dia = 0;
int mes = 0;
int anyo = 0;
int hora = 0;
int minuto = 0;
int segundo = 0;
int alarmMinuto = 0;
int alarmHora = 0;
int alarmSegundo = 5;
int alMinutoDia;
int alHoraDia;
int alSegDia;
String DD;
String MM;
String AAAA;
String HH = "";
String MIN = "";
String SEG = "";
String input = "";
String hh = "";
String mm = "";
// -------------   alarms ID -------------------------------------
int alMonday;
int alTuesday;
int alWednesday;
int alThursday;
int alFriday;
int alSaturday;
int alSunday;
//--------------  auxiliary --------------------------------------
char c;
String instruct = "";
int primerNumero = 0;
String serialData = "";
unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long intervalo = 3000;
String respuesta = "";
int flag[7];
// ---------------  pin definition -------------------------------
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 4;
const int buzzPin = 6;
const int desfase = 10;
// -----------------  duty cycle --------------------------------
const int redInt = 254;
const int greenInt = 254;
const int blueInt = 255;
// --------------------- other variables -------------------------
int k = 0;
int kD = 0;
//--------------  object creation   ------------------------------
StopWatch reloj(StopWatch::SECONDS);
//=== function1 to print the command list:  ===========================
void printHelp1() {
  Serial.println ("Instrucciones para ajustes del calendario Rufus");
  Serial.println ("Calendario: Introduzca el dígito '1' y luego en orden y con dos digitos");
  Serial.print ("dia: DD, mes: MM, anyo: AAAA\t");
  Serial.println ("Termine con un '/' ");
}
//=== function2 to print the command list:  ===========================
void printHelp2() {
  Serial.println ("Instrucciones para ajustes del reloj Rufus");
  Serial.print ("2. Hora: Introduzca el dígito '2' y luego en orden la hora: HH y minutos: MM\t");
  Serial.println ("Termine con un '/' ");
}
//=== function3 to print the command list:  ===========================
void printHelp3() {
  Serial.println ("Instrucciones para ajustes de la alarma Rufus");
  Serial.print ("3. Hora: Introduzca el dígito '3' y luego en orden la hora: HH y minutos: MM\t");
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
      switch (*devol2) {
        case 1 :
          Serial.print("datos de fecha: "); Serial.println(salida.substring(1, 3) + "-" + salida.substring(3, 5) + "-" + salida.substring(5, 9));
          break;
        case 2 :
          Serial.print("datos de hora: "); Serial.println(salida.substring(1, 3) + ":" + salida.substring(3, 5) + ":" + salida.substring(5, 7));
          break;
        case 3 :
          Serial.print ("datos de alarma: "); Serial.println(salida.substring(1, 3) + ":" + salida.substring(3, 5));
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
  alMinutoDia = alarmMinuto;
  alHoraDia = alarmHora;
  alSegDia = alarmSegundo + desfase;

}

//=== function alarm Service : ===========================================
void Alarma() {
  flag[Alarm.getTriggeredAlarmId()] = 1;
  reloj.start();
  }
void lightAndSound() {
   if (reloj.elapsed()<= 5) {
    digitalWrite(redPin, redInt);
    analogWrite(buzzPin, 127);
  }
  else if (reloj.elapsed() > 5 && k <= reloj.elapsed()) {
    digitalWrite(redPin, redInt / 2); digitalWrite(greenPin, greenInt / 2);
    analogWrite(buzzPin, 0);
  }
  else if (reloj.elapsed() > 6 && reloj.elapsed() <= 11) {
    digitalWrite(greenPin, greenInt);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 34);
  }
  else if (reloj.elapsed() > 11 && reloj.elapsed() <= 13) {
    digitalWrite(greenPin, greenInt / 2); digitalWrite(bluePin, blueInt / 2);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 0);
  }
  else if (reloj.elapsed() > 13 && reloj.elapsed() <= 18) {
    digitalWrite(bluePin, greenInt);
    digitalWrite(greenPin, 0);
    analogWrite(buzzPin, 205);
  }
  else {
    digitalWrite(greenPin, 0);
    digitalWrite(bluePin, 0);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 0);
    flag[0] = 0;
    reloj.reset();
    for (int ID=0;ID<5;++ID){
    Alarm.disable (ID);//we must enable the alarm later.
  }
  }
}


//---------------- setup ---------------------------------------------
void setup() {
  while (!Serial);
  setTime(0, 0, 0, 1, 1, 1970);
  Serial.begin(9600);   // Open serial port (9600 bauds).
  printHelp1();          // Print the command list.
  Serial.println ("comienzo el esto ");
  Serial.print ("fecha inicial "); Serial.printf ("%d-%d-%d.\n", day(), month(), year());
  printHelp2();
  Serial.print ("hora inicial "); Serial.printf ("%d:%d:%d.\n", hour(), minute(), second());
  printHelp3();
  Serial.print ("alarma inicial "); Serial.printf ("%d:%d:%d.\n", 0, 0, 0);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  digitalWrite(redPin, 0);
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 0);
  alMonday=Alarm.alarmRepeat(dowMonday, alarmHora, alarmMinuto,  alarmSegundo, Alarma);
  alTuesday=Alarm.alarmRepeat(dowTuesday, alarmHora, alarmMinuto,  alarmSegundo, Alarma);
  alWednesday= Alarm.alarmRepeat(dowWednesday, alarmHora, alarmMinuto,  alarmSegundo, Alarma);
  alThursday=Alarm.alarmRepeat(dowThursday, alarmHora, alarmMinuto,  alarmSegundo, Alarma);
  alFriday=Alarm.alarmRepeat(dowFriday, alarmHora, alarmMinuto,  alarmSegundo, Alarma);
  alSaturday=Alarm.alarmRepeat(dowSaturday, alarmHora + 3, alarmMinuto,  alarmSegundo, Alarma);
  alSunday=Alarm.alarmRepeat(dowSunday, alarmHora + 3, alarmMinuto,  alarmSegundo, Alarma);
  for (int i = 0; i < 7;++i) {
    flag[i] = 0;
  }

}
//---------------- loop ---------------------------------------------

void loop() {
  currentMillis = millis();

  while ((Serial.available()) && (dia == 0 && mes == 0 && anyo == 0) || (hora == 0 && minuto == 0 && segundo == 0) || (alarmHora == 0 && alarmMinuto == 0)) {
    getEntry(&serialData, &primerNumero);
    stringtoNumber(serialData);
    setTime(hora, minuto, segundo, dia, mes, anyo);
  }

  if (currentMillis - previousMillis >= intervalo ) // this prevents the time from being constantly shown.
  { previousMillis = currentMillis;
    Serial.print ("\nserialData\t"); Serial.println (serialData);
    Serial.printf ("Fecha: %d-%d-%d. Hora: %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
    Serial.printf ("Alarma: %d:%d:%d\n", alarmHora, alarmMinuto, 10);
    Serial.printf ("Alarma diaria: %d:%d:%d\n", alHoraDia, alMinutoDia, alSegDia);
  }
  else {
    Serial.print("");
  }
  if (flag[0]==1){
    lightAndSound();
    }

  Alarm.delay(0);
}
