unsigned long serialdata = 0;
int inbyte;
int ledPin;
int blinkRate;
int var;
void setup(){
  Serial.begin(9600); //Activo el monitor
}

void loop() {
  serialdata = getSerial(); // ahora bifurcaremos los tratamientos según el valor de la cadena de números con un switch
  String thisString = String (serialdata);
  Serial.print ("serialdata ");Serial.println (serialdata,DEC);
  Serial.print ("thisString ");Serial.println (thisString);
 char primerNumero = thisString.charAt(0);
 Serial.print ("primerNumero");Serial.println (primerNumero);
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


