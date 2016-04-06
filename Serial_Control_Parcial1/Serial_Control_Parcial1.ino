
//1. calendario
int dia = 0;
int mes = 0;
int anyo = 0;
int hora;
int minuto = 0;
int segundo = 0;
int alarmMinuto = 0;
int alarmHora = 0;

//VARIABLES AUXILIARES
String DD;
String MM;
String AAAA;
String HH = "";
String MIN = "";
String SEG = "";
String input = "";
String hh = "";
String mm = "";
char c;
String instruct = "";
int primerNumero = 0;
String serialData = "";
unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long intervalo = 2000;
String respuesta = "";

#include <Time.h>
#include <TimeAlarms.h>
#include <avr/wdt.h>

//=== function1 to print the command list:  ===========================
void printHelp1() {
  Serial.println ("Instrucciones para ajustes del calendario Rufus");
  Serial.println ("Calendario: Introduzca en este orden y con dos digitos");
  Serial.print ("dia: DD, mes: MM, anyo: AAAA\t");
  Serial.println ("Termine con un '/' ");
}
//=== function2 to print the command list:  ===========================
void printHelp2() {
  Serial.println ("Instrucciones para ajustes del reloj Rufus");
  Serial.print ("2. Hora: Introduzca la hora: HH y minutos: MM");
  Serial.println ("Termine con un '/' ");
}
//=== function3 to print the command list:  ===========================
void printHelp3() {
  Serial.println ("Instrucciones para ajustes de la ralarma Rufus");
  Serial.print ("3. Hora: Introduzca la hora: HH y minutos: MM");
  Serial.println ("Termine con un '/' ");
}
//=== function collect data:  ==========================================
void getEntry(String *devol1, int *devol2) {
  String salida = "";
  // Read any serial input
  while (Serial.available() > 0)
  {
    c = (char) Serial.read();
    Serial.print("input caracter "); Serial.println(c);
    input = input + c; // Read in one char at a time
    delay(5); // Delay for 5 ms so the next char has time to be received
    Serial.print("inputagregado "); Serial.println(input);
    Serial.print("longitud "); Serial.println(input.length());
    Serial.print("Ultimo character "); Serial.println(input[input.length() - 1]);
    if (input[input.length() - 1] == '/') {
      salida = input.substring(0, input.length() - 1);
      Serial.print("inputanesimo de salida "); Serial.println(salida);
      input = "";
      *devol1 = salida;
      *devol2 = salida[0] - '0';
    }
  }
}
//=== function convert strings to nuneric for Calendar :  =========================
void stringtoNumber1(String instruct) {
  DD = instruct.substring(1, 3);
  MM = instruct.substring(3, 5);
  AAAA = instruct.substring(5, 9);
  dia = DD.toInt();
  mes = MM.toInt();
  anyo = AAAA.toInt();
 
}
//=== function convert strings to nuneric for Time :  =========================

void stringtoNumber2(String instruct) {
  HH = instruct.substring(1, 3);
  MIN = instruct.substring(3, 5);
  SEG = instruct.substring(5, 7 );
  hora = HH.toInt();
  minuto = MIN.toInt();
  segundo = SEG.toInt();
  setTime(hora, minuto, segundo, dia, mes, anyo);
}
//=== function convert strings to nuneric for Alarms :  =========================

void stringtoNumber3(String instruct) {
  hh = instruct.substring(1, 3);
  mm = instruct.substring(3, 5);
  alarmHora = hh.toInt();
  alarmMinuto = mm.toInt();
  Alarm.timerRepeat(15, aSr);
}
//=== function alarm Service : ================================================
void aSr() {
  Serial.println("me toca sonar la alarma");
}
//=== function confirm/neg-ation : ================================================
void getConfirm(String *devol1) {
  String salida = "";
  // Read any serial input
  while (Serial.available() > 0)
  {
    c = (char) Serial.read();
    Serial.print("input caracter "); Serial.println(c);
    input = input + c; // Read in one char at a time
    delay(5); // Delay for 5 ms so the next char has time to be received
    Serial.print("inputagregado "); Serial.println(input);
    Serial.print("longitud "); Serial.println(input.length());
    Serial.print("Ultimo character "); Serial.println(input[input.length() - 1]);
    if (input[input.length() - 1] == '/') {
      salida = input.substring(0, input.length() - 1);
      Serial.print("inputanesimo de salida "); Serial.println(salida);
      input = "";
      *devol1 = salida;
    }
  }
}

//=================  function that sets parameters : ===============================
void setTiempo() {
  getEntry(&instruct, &primerNumero);
  switch (primerNumero) {
    case 1 :
      stringtoNumber1(instruct);
      Serial.print ("Es esta la fecha? :"); Serial.print (dia); Serial.print ("/");
      Serial.print (mes); Serial.print ("/"); Serial.println (anyo);
      Serial.println("teclee si o no seguido de /");
      //while (!Serial.available());
      getConfirm(&respuesta);
      Serial.print("respuesta : ");Serial.println(respuesta);
      if(respuesta=="si"){
      setTime(0, 0, 0, dia, mes, anyo);
      }
      break;
case 2 :
  stringtoNumber2(instruct);
  Serial.print ("Es esta la hora? :"); Serial.print (hora); Serial.print (":");
  Serial.print (minuto); Serial.print (":"); Serial.println (segundo);
  Serial.println("teclee si o no seguido de /");
  break;
case 3 :
  stringtoNumber3(instruct);
  Serial.print ("Es esta la hora de la lalarma ? :"); Serial.print (alarmHora); Serial.print (":");
  Serial.println (alarmMinuto);
  Serial.println("teclee si o no seguido de /");
   break;
  //default : /* Optional */
  //Serial.println ("Error; ha incluido un numero distinto de 1 , 2 o 3");
  //break;
}
}

//---------------- setup ---------------------------------------------
void setup() {

  while (!Serial);
  wdt_disable(); // Desactivar el watchdog
  Serial.begin(9600);   // Open serial port (9600 bauds).
  printHelp1();          // Print the command list.
  Serial.println ("comienzo el esto ");
  Serial.print ("fecha inicial "); Serial.printf ("%d-%d-%d.\n", day(), month(), year());
 /* printHelp2();
  Serial.print ("hora inicial "); Serial.printf ("%d:%d:%d.\n", hour(), minute(), second());
  printHelp3();
  Serial.print ("Alaema inicial "); Serial.printf ("%d:%d:%d.\n", 0, 0, 0);*/

}
//---------------- loop ---------------------------------------------

void loop() {

  while (dia != 0 && mes != 0 || anyo != 0) {
    setTiempo();
  }
 /* while ((dia != 0 && mes != 0 && anyo != 0) && (hora == 0 && minuto == 0 && segundo == 0)) {
    getEntry(&serialData, &primerNumero);
    setTiempo(serialData);
  }
  while ((dia != 0 && mes != 0 && anyo != 0) && (hora != 0 && minuto != 0 && segundo != 0) && (alarmHora == 0 && alarmMinuto == 0)) {
    getEntry(&serialData, &primerNumero);
    setTiempo(serialData);
  }*/
  currentMillis = millis();
  if ((currentMillis - previousMillis >= intervalo) && (dia != 0 && mes != 0 && anyo != 0)) {

    previousMillis = currentMillis;
    Serial.printf ("%d-%d-%d. %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
  }
  else {
    Serial.print("");
  }

}



