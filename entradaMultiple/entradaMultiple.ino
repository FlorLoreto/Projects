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
  { Serial.print("input caracter "); Serial.println(input);
    c = (char) Serial.read();
    input = input + c; // Read in one char at a time
    delay(5); // Delay for 5 ms so the next char has time to be received
    Serial.print("inputagregado "); Serial.println(input);
    Serial.print("longitud "); Serial.println(input.length());
    Serial.print("último character "); Serial.println(input[input.length() - 1]);
    if (input[input.length() - 1] == '/') {
      salida = input.substring(0, input.length() - 1);
      Serial.print("inputanésimo de salida "); Serial.println(salida);
      input = "";
    }
  } return salida;
}

//Funcion que confirma los ajustes
int getConfirm (int primerNumero, String instruct, String answer){
switch(primerNumero){
  case 1 :
  do  {
  Serial.print ("Es esta la fecha? :");Serial.print (instruct.substring(1,2));Serial.print ("/");
  Serial.print (instruct.substring(3,4));Serial.print ("/");Serial.println (instruct.substring(5,8));
  Serial.println("teclee si o no seguido de /");
  answer=getEntry();}
  while (answer!="si");
  DD=instruct.substring(1,2);
  MM=instruct.substring(3,4);
  AAAA=instruct.substring(5,8);
  dia = DD.toInt();
  mes = MM.toInt();
  anyo = AAAA.toInt();
  break; 
  case 2 :
  do  {
  Serial.print ("Es esta la hora? :");Serial.print (instruct.substring(1,2));Serial.print (":");
  Serial.print (instruct.substring(3,4));Serial.print (":");Serial.println (instruct.substring(5,6));
  Serial.println("teclee si o no seguido de /");
  answer=getEntry();}
  while (answer!="si");
  HH=instruct.substring(1,2);
  MIN=instruct.substring(3,4);
  SEG=instruct.substring(5,8);
   hora = HH.toInt();
   minuto = MIN.toInt();
   segundo = SEG.toInt();
  break; 
  case 3 :
  do  {
  Serial.print ("Es esta la hora de la alarma ? :");Serial.print (instruct.substring(1,2));Serial.print (":");
  Serial.println (instruct.substring(3,4));
  Serial.println("teclee si o no seguido de /");
  answer=getEntry();}
  while (answer!="si");
  hh=instruct.substring(1,2);
  mm=instruct.substring(3,4);
  alarmHora = hh.toInt();
  alarmMinuto = mm.toInt();
  break; 
  default : /* Optional */
  Serial.println ("Error; ha incluido un numero distinto de 1 , 2 o 3");
   }return primerNumero;
   setTime(hora, minuto, 0, dia, mes, anyo);
}

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
  /*int nAjuste=0;
  do{
  dataEntry=getEntry();
  int primerNumero=dataEntry[0]-'0';
  nAjuste=getConfirm(primerNumero,dataEntry,answer);}
  while (0<nAjuste<3);
  Serial.print ("Calendario :");Serial.printf ("%d-%d-%d\n",dia,mes,anyo);
  Serial.print ("Reloj :");Serial.printf ("%d:%d:%d\n",hora,minuto,segundo);
 Serial.print ("Alarma :");Serial.printf ("%d:%d\n",alarmHora,alarmMinuto);*/
  }

void loop() {
  while(!Serial);
  getEntry();
     
}



