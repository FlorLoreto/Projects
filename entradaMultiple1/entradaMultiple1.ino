//fija la fecha y la hora del artefacto
//include libraries
#include <Time.h>
#include <TimerOne.h>
#include <TimeAlarms.h>
/*
  Variables a determinar
*/

//1. calendario
int dia;
int mes;
int anyo;
int hora;
int minuto;
int segundo;
//2. alarmas
int alarmMinuto;
int alarmHora;
/*
*/
int primerNumero=0;
unsigned serialdata; //contenedor de los datos introducidos por el recto
int var = 0;
char inbyte;
//VARIABLES AUXILIARES
String DD;
String MM;
String AAAA;
String HH;
String MIN;
String SEG;
String hh;
String mm;
String confirm;
String input = "";
char c;
String instruct = "";
String answer = "";
String dataEntry="";
// Es la función que devuelve las ristras de números y borra el buffer cuando se ha recibe un '/'
String getEntry() {
  String salida = "";
  // Read any serial input
  while (Serial.available() > 0)
  {// Serial.print("input caracter "); Serial.println(input);
    c = (char) Serial.read();
    input = input + c; // Read in one char at a time
    delay(5); // Delay for 5 ms so the next char has time to be received
   /* Serial.print("inputagregado "); Serial.println(input);
    Serial.print("longitud "); Serial.println(input.length());
    Serial.print("último character "); Serial.println(input[input.length() - 1]);*/
    if (input[input.length() - 1] == '/') {
      salida = input.substring(0, input.length() - 1);
     Serial.print("inputanésimo de salida "); Serial.println(salida);
      input = "";
    }
  } return salida;
}

//Funcion que confirma los ajustes

void setup() {/*Se supone que debo tener los ajustes hechos*/
  Serial.begin(9600); //Activo el monitor
  Serial.println ("Instrucciones para ajustes del reloj Rufus");
  Serial.println ("1. Calendario: Introduzca en este orden y con dos digitos");
  Serial.print ("dia: DD, mes: MM, anyo: AAAA\t");
  Serial.println ("Termine con un '/' ");
  Serial.print ("2. Hora: Introduzca la hora: HH y minutos: MM");
  Serial.println ("Termine con un '/' ");
  Serial.print ("3. Alarmas:  Introduzca la hora: HH y minutos: MM en que debe dispararse la alarma de lunes a viernes ");
  Serial.println ("Termine con un '/' ");
   int nAjuste=0;
  dataEntry=getEntry();
  int primerNumero=dataEntry[0]-'0';
   Serial.print ("Calendario :");Serial.printf ("%d-%d-%d\n",dia,mes,anyo);
  Serial.print ("Reloj :");Serial.printf ("%d:%d:%d\n",hora,minuto,segundo);
  Serial.print ("Alarma :");Serial.printf ("%d:%d\n",alarmHora,alarmMinuto);
  }

void loop() {
     
}



