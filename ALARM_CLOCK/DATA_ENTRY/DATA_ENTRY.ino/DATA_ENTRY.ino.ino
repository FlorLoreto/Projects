
//==================  Libraries ===============================
#include <Time.h>
//==================== Variables ===============================
//---------------  date & time -------------------------------
int dia;
int mes ;
int anyo;
int hora = 0;
int minuto = 0;
int segundo = 0;
String WiFiSSID = "";
String WAP="";
String DD;
String MM;
String AAAA;
String HH = "";
String MIN = "";
String SEG = "";
String hh = "";
String mm = "";
//------------  time measurement -------------------------------
unsigned long currentMillis;
unsigned long previousMillis;
unsigned long intervalo = 1000;
//--------------  auxiliary -------------------------------------
char caracter;
String dataEntry = "";
String input = "";
int primerNumero = 0;
String respuesta = "";
boolean finAjuste = false;
int flag;
String serialData = "";
int k = 0;
//=== function1 to print the command list:  ===========================
void printHelp1() {
  Serial.println ("*********Instrucciones para WiFi ID***************");
  Serial.println ("1. SSID: Introduzca el digito '1' y luego los caracteres de la SSID (WLAN_A31A p.e.)");
  Serial.print ("WLAN_A31A\t");
  Serial.println ("Termine con un '/' ");
}
//=== function2 to print the command list:  ===========================
void printHelp2() {
  Serial.println ("************Instrucciones WiFi clave WAP2 ******************");
  Serial.print ("2. clave WAP2: Introduzca el digito '2' y luego en orden la clave \t");
  Serial.println ("Termine con un '/' ");
}
//=== function to collect data throgh serial monitor:  ==================
void getEntry(String * devol1, int *devol2) {
  String salida = "";
  // Read any serial input
  while (Serial.available() > 0)
  {
    caracter = (char) Serial.read();
    Serial.print("input caracter "); Serial.println(caracter);
    input = input + caracter; // Read in one char at a time
    if (input[input.length() - 1] == '/') {
      salida = input.substring(0, input.length() - 1);
      Serial.print("input de salida "); Serial.println(salida);
      input = "";
      *devol1 = salida;
      *devol2 = salida[0] - '0';//
      Serial.printf("tipo datos   %d, %d\n", *devol2, salida[0]);
      switch (*devol2) {
        case 1 :
          Serial.print("SSID: "); Serial.println(salida);
          Serial.flush();
          break;
        case 2 :
          Serial.print("clave WAP2: "); Serial.println(salida);
          Serial.flush();
          break;
      }
    }
  }
   finAjuste = true;
}
//=== function convert strings to nuneric :  ====================
void stringtoNumber(String dataEntry) {

  if (dataEntry.substring(0, 1) == "1") {
    DD = dataEntry.substring(1, 3);
    MM = dataEntry.substring(3, 5);
    AAAA = dataEntry.substring(5, 9);
    dia = DD.toInt();
    mes = MM.toInt();
    anyo = AAAA.toInt();
    k = 1;

  }
  if (dataEntry.substring(0, 1) == "2") {
    HH = dataEntry.substring(1, 3);
    MIN = dataEntry.substring(3, 5);
    SEG = dataEntry.substring(5, 7 );
    hora = HH.toInt();
    minuto = MIN.toInt();
    segundo = SEG.toInt();
    k = 2;
    setTime(hora, minuto, segundo, dia, mes, anyo);
  }
  if (k == 2) {// Define end of adjustment, setTime and declare Alarms.
    finAjuste = true;
  }
}
//******************  sketch body **************************************/
//===================  setup() ===========================================
void setup() {
  while (!Serial);
  Serial.begin(9600);   // Open serial port (9600 bauds).
  //----------  Initial screen -----------------------
  printHelp1();
  printHelp2();
  }
//=================  main loop() ============================================
void loop() {
  //----------------  Data Entry (date, time settings) ----------------
  while (finAjuste == false )
  { getEntry(&serialData, &primerNumero);
    stringtoNumber(serialData);
  }
  //----------------------  Others ----------------------------------------------------
  currentMillis = millis();
  if (currentMillis - previousMillis >= intervalo) // this prevents the time from being constantly shown.
  { previousMillis = currentMillis;
    Serial.printf ("Fecha: %d-%d-%d. Hora: %d:%d:%d\n", day(), month(), year(), hour(), minute(), second());
  }

}
