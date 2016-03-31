//fija la fecha y la hora del artefacto
//Serial.readString() reads characters from the serial buffer into a string. The function terminates if it times out (see setTimeout()).
//Serial.setTimeout() sets the maximum milliseconds to wait for serial data when using Serial.readBytesUntil(), 
//Serial.readBytes(), Serial.parseInt() or Serial.parseFloat(). It defaults to 1000 milliseconds.
#include <Time.h>

/*
Variables a determinar
*/

//1. calenario
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
unsigned long serialdata; //contenedor de los datos introducidos por el recto
int var=0;

void setup(){
  Serial.begin(9600); //Activo el monitor
  Serial.println ("Instrucciones para ajustes del reloj Rufus");
  Serial.println ("1. Calendario: Introduzca en este orden y con dos digitos");
  Serial.print ("dia: DD, mes: MM, anyo: AAAA\t");
  Serial.println ("Termine con un '\' ");
  Serial.print ("2. Alarmas_ Introduzca la hora: HH y minutos: MM en que debe dispararse la alarma de lunes a viernes ");
  Serial.println ("Termine con un '\' ");
   
}

void loop() {
  /*
  Capturaremos las entradas
  */
  serialdata = getSerial(); // recibe las ristras de números y borra el buffer cuando se ha recibe un '/'
  String thisString = String (serialdata);
  Serial.print ("serialdata ");Serial.println (serialdata,DEC);
  Serial.print ("thisString ");Serial.println (thisString);
 char primerNumero = thisString.charAt(0);
 Serial.print ("primerNumero");Serial.println (primerNumero);
 // ahora bifurcaremos los tratamientos según el valor de la cadena de números con un switch
 if (primerNumero=='1'){
  var=1;}
// String pepino=primerNumero;
  //int primoNumero=atoi (pepino);//primerNumero es inmodificable
  String rest;
  for (int i = 1; i < thisString.length(); ++i) {
    rest = rest + thisString.charAt(i);
     Serial.print ("rest ");Serial.println (rest);
  }
  int datoUtil = rest.toInt();Serial.print ("datoUtil ");Serial.println (datoUtil );
  Serial.print ("primerNumero ");Serial.println (primerNumero);
  Serial.print ("1+primerNumero");Serial.println (1+primerNumero);
  delay(10000);
  //leep all the characters out of the first

  //int primo=primerNumero.toInt();
  switch (var)
  {
    case 1://ledPin definition
      Serial.print("ledPin "); Serial.println(datoUtil);
      ledPin = datoUtil;
      break;

case 2://blinkRate definition

      blinkRate = datoUtil;
      break;

  }
}
// Es la función que devuelve las ristras de números y borra el buffer cuando se ha recibe un '/'
long getSerial()
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
    else if (inbyte > 0 && inbyte == '/') {
      Serial.print("serialdata final "); Serial.println(serialdata);
    }
  }

  return serialdata;
  inbyte = 0;
}


