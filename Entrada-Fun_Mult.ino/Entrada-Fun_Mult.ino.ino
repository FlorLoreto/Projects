//1. calendario
int dia;
int mes;
int anyo;
int hora;
int minuto = 0;
int segundo = 0;
//2. alarmas
int alarmMinuto = 0;
int alarmHora = 0;
/*
*/
int primerNumero = 0;
unsigned serialdata; //contenedor de los datos introducidos por el recto
int var = 0;
char inbyte;
//VARIABLES AUXILIARES
String DD;
String MM;
String AAAA;
String HH = "";
String MIN = "";
String SEG = "";
String hh = "";
String mm = "";
String confirm;
String input = "";
char c;
String instruct = "";
String answer = "";
String dataEntry = "";
String caracter = "";
int numero;


#include <TimerOne.h>

#include <TimeAlarms.h>

#include <Time.h>

/**
  Reads data entered through Serial Monitor
**/


void setup() {
  while (!Serial) ;
  Serial.begin(9600);
  Serial.println ("Instrucciones para ajustes del reloj Rufus");
  Serial.println ("1. Calendario: Introduzca en este orden y con dos digitos");
  Serial.print ("dia: DD, mes: MM, anyo: AAAA\t");
  Serial.println ("Termine con un '/' ");
  Serial.print ("2. Hora: Introduzca la hora: HH y minutos: MM");
  Serial.println ("Termine con un '/' ");
  Serial.print ("3. Alarmas:  Introduzca la hora: HH y minutos: MM en que debe dispararse la alarma de lunes a viernes ");
  Serial.println ("Termine con un '/' ");

}

void loop()
{
  if (timeStatus() != timeSet &&   (HH == "" || MIN == "" || SEG == "" || hh == "" || mm == "")) {
   getSettings ();
  }
}



void getEntry(String *devol1, int *devol2) {
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
      *devol1 = salida;
      *devol2 = salida[0] - '0';
    }
  }
}

void getSettings () {
  getEntry(&instruct, &primerNumero);
  switch (primerNumero) {
    case 1 :
      Serial.print ("Es esta la fecha? :"); Serial.print (instruct.substring(1, 2)); Serial.print ("/");
      Serial.print (instruct.substring(3, 4)); Serial.print ("/"); Serial.println (instruct.substring(5, 8));
      Serial.println("teclee si o no seguido de /");
      DD = instruct.substring(1, 2);
      MM = instruct.substring(3, 4);
      AAAA = instruct.substring(5, 8);

      break;
    case 2 :
      Serial.print ("Es esta la hora? :"); Serial.print (instruct.substring(1, 2)); Serial.print (":");
      Serial.print (instruct.substring(3, 4)); Serial.print (":"); Serial.println (instruct.substring(5, 6));
      Serial.println("teclee si o no seguido de /");
      HH = instruct.substring(1, 2);
      MIN = instruct.substring(3, 4);
      SEG = instruct.substring(5, 8);
      break;
    case 3 :
      Serial.print ("Es esta la hora de la lalarma ? :"); Serial.print (instruct.substring(1, 2)); Serial.print (":");
      Serial.println (instruct.substring(3, 4));
      Serial.println("teclee si o no seguido de /");
      hh = instruct.substring(1, 2);
      mm = instruct.substring(3, 4);
      break;
    default : /* Optional */
      Serial.println ("Error; ha incluido un numero distinto de 1 , 2 o 3");
      break;
  }
}
