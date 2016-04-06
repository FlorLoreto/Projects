//1. calendario
int dia = 0;
int mes = 0;
int anyo = 0;
int hora;
int minuto = 0;
int segundo = 0;

//VARIABLES AUXILIARES
String DD;
String MM;
String AAAA;
String HH = "";
String MIN = "";
String SEG = "";
String input = "";
char c;
String instruct = "";
int primerNumero = 0;
String serialData = "";
unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long intervalo = 2000;

#include <Time.h>

//=== function to print the command list:  ===========================
void printHelp() {
  Serial.println ("Instrucciones para ajustes del calendario Rufus");
  Serial.println ("Calendario: Introduzca en este orden y con dos digitos");
  Serial.print ("dia: DD, mes: MM, anyo: AAAA\t");
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
//=== function convert strings to nuneric :  =================================
void stringtoNumber(String instruct) {
  DD = instruct.substring(1, 3);
  MM = instruct.substring(3, 5);
  AAAA = instruct.substring(5, 9);
  dia = DD.toInt();
  mes = MM.toInt();
  anyo = AAAA.toInt();
  setTime(0, 0, 0, dia, mes, anyo);
}

//---------------- setup ---------------------------------------------
void setup() {
  
  while (!Serial);
  Serial.begin(9600);   // Open serial port (9600 bauds).
  printHelp();          // Print the command list.
  Serial.println ("comienzo el esto ");
  Serial.print ("hora inicial "); Serial.printf ("%d-%d-%d. %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());

}
//---------------- loop ---------------------------------------------

void loop() {
  
  while (dia == 0 && mes == 0 || anyo == 0) {
    getEntry(&serialData, &primerNumero);
    stringtoNumber(serialData);
  }
  currentMillis = millis();
  if ((currentMillis - previousMillis >= intervalo)&& (dia != 0 && mes != 0 && anyo != 0)) {

    previousMillis = currentMillis;
          Serial.printf ("%d-%d-%d. %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
     }
  else {
    Serial.print("");
  }

}



