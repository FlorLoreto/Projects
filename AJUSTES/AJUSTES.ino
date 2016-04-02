//fija la fecha y la hora del artefacto
//Serial.readString() reads characters from the serial buffer into a string. The function terminates if it times out (see setTimeout()).
//Serial.setTimeout() sets the maximum milliseconds to wait for serial data when using Serial.readBytesUntil(),
//Serial.readBytes(), Serial.parseInt() or Serial.parseFloat(). It defaults to 1000 milliseconds.
#include <Time.h>
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
int primerNumero;
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

//String inputData;
// Es la función que devuelve las ristras de números y borra el buffer cuando se ha recibe un '/'
unsigned getSerial()
{
  serialdata = 0;
  while (inbyte != '/')
  {
    inbyte = Serial.read();

    if (inbyte > 0 && inbyte != '/')//'/' es el indicador de fin de número. mientras haya entradas, adicionamos
    {
      serialdata = serialdata * 10 + inbyte - '0';

      Serial.print("serialdata "); Serial.println(serialdata);
    }
    else if (inbyte > 0 && inbyte ==  '/') {
      Serial.print("serialdata final "); Serial.println(serialdata);
    }
  }

  return serialdata;
  inbyte = 0;
}
//Otra funcion
//Funcion que actualiza los ajustes
void setClockAlarm(int primerNumero, String entraData) {

  switch (primerNumero) {
    case 1 :
      DD = entraData.charAt(0) + entraData.charAt(1);
      dia = DD.toInt();
      MM = entraData.charAt(2) + entraData.charAt(3);
      mes = MM.toInt();
      AAAA = entraData.charAt(4) + entraData.charAt(5) + entraData.charAt(6) + entraData.charAt(7);
      anyo = AAAA.toInt();
      Serial.print ("Case 1 "); Serial.printf ("Dia %d, Mes %d, Anno %d\n", dia, mes, anyo);
      break;
    case 2 :
      HH = entraData.charAt(0) + entraData.charAt(1);
      hora = DD.toInt();
      MIN = entraData.charAt(2) + entraData.charAt(3);
      minuto = MIN.toInt();
      SEG = entraData.charAt(4) + entraData.charAt(5);
      segundo = SEG.toInt();
      Serial.print ("Case 2 "); Serial.printf ("Hora %d, Minuto %d, Segundo %d\n", hora, minuto, segundo);
      break;
    case 3 :
      hh = entraData.charAt(0) + entraData.charAt(1);
      alarmHora = hh.toInt();
      mm = entraData.charAt(2) + entraData.charAt(3);
      alarmMinuto = mm.toInt();
      Serial.print ("Case 3 "); Serial.printf ("Hora alarma %d, Minuto alarma %d \n", alarmHora, alarmMinuto);
      break;
    default : /* Optional */
      Serial.println ("Error; ha incluido un numero distinto de 1 y 2");
  }
}
void setup() {
  Serial.begin(9600); //Activo el monitor
  Serial.println ("Instrucciones para ajustes del reloj Rufus");
  Serial.println ("1. Calendario: Introduzca en este orden y con dos digitos");
  Serial.print ("dia: DD, mes: MM, anyo: AAAA\t");
  Serial.println ("Termine con un '/' ");
  Serial.print ("2. Hora: Introduzca la hora: HH y minutos: MM");
  Serial.println ("Termine con un '/' ");
  Serial.print ("3. Alarmas:  Introduzca la hora: HH y minutos: MM en que debe dispararse la alarma de lunes a viernes ");
  Serial.println ("Termine con un '/' ");

}

void loop() {
  /*
    Capturaremos las entradas
  */
  serialdata = getSerial(); // recibe las ristras de números y borra el buffer cuando se ha recibe un '/'
  String thisString = String (serialdata);
  Serial.print ("serialdata "); Serial.println (serialdata, DEC);
  Serial.print ("thisString "); Serial.println (thisString);
  char orden[thisString.length()];
  for (int i = 0; i < thisString.length(); ++i) {
    String numberString = String(i);
    String orden = "Numero" + numberString;
    orden[i] = thisString.charAt(i);
  }
  int rank = atoi(orden);
  char ichiBan = orden[0];
  if (ichiBan == 1) {
    primerNumero = 1;
  }
  else if ((ichiBan == 2)) {
    primerNumero = 2;
  }
  else if ((ichiBan == 3)) {
    primerNumero = 3;
  }
  else {
    Serial.print ("la seleccion hecha no está en 1, 2 o 3: "); Serial.print (primerNumero);Serial.print("ichiban");Serial.println ichiban)
    delay(5000);
  }
String inputData;
  for (int i = 1; i < thisString.length(); ++i) {
    inputData = inputData + thisString[i];
  }

  setClockAlarm(primerNumero, inputData);

  for (int i = 1; i < thisString.length(); ++i) {
    inputData = inputData + thisString.charAt(i);//
  }
  // Serial.print ("Case # ");Serial.println (thisString.charAt(0));
  // Serial.print ("inputData ");Serial.println (inputData);
  delay(1000);
}



