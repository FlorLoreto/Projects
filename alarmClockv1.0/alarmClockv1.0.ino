//This sketch will handle an Alarm Clock
//import libraries
//include libraries
#include <Time.h>
#include <TimerOne.h>
#include <TimeAlarms.h>
#include <avr/wdt.h>
// I. Variables declaration
//1. calendar
int dia;
int mes;
int anyo;
String DD;
String MM;
String AAAA;
//2. clock
int hora;
int minuto;
int segundo;
String HH;
String MIN;
String SEG;
//3. alarms
int alarmMinuto;
int alarmHora;
String hh;
String mm;
//4. Pins
int redPin;
int  greenPin;
int bluePin ;
int  buzzerPin;
int  switchPin;
//5. Auxiliary
int primerNumero = 0;
String confirm;
String input = "";
char c;
String instruct = "";
String answer = "";
String dataEntry = ""; //contenedor de los datos introducidos por el recto
volatile int flag;
int k=0;
unsigned long intervalo;
long unsigned previousMillis;
long unsigned currentMillis;
int state;
/*
Funciones
*/
// Setting calendar and time
String getEntry(){String salida="";
  // Read any serial input
     while (Serial.available() > 0)
     {Serial.print("input1 ");Serial.println(input); c=(char) Serial.read();
        input =input+c; // Read in one char at a time
         delay(5); // Delay for 5 ms so the next char has time to be received
        Serial.print("inputilloagregado ");Serial.println(input); 
        Serial.print("longitud ");Serial.println(input.length()); 
        Serial.print("último character ");Serial.println(input[input.length()-1]); 
  if (input[input.length()-1]=='/'){
  salida=input.substring(0,input.length()-1);
  Serial.print("inputanésimo ");Serial.println(salida);
  input=""; }            
 }return salida;  
  }
//confirm settings
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
//ISR PARA PULSACION DE BOTON

void Reset()
{
  wdt_enable(WDTO_1S);
  while (1);
}



// Alarm is always programmed from Monday (weekday 2) to Friday (weekday 6)
void setup() {
  /*Se supone que debo tener los ajustes hechos*/
  Serial.begin(9600); //Activo el monitor
  Serial.println ("Instrucciones para ajustes del reloj Rufus");
  Serial.println ("1. Calendario: Introduzca en este orden y con dos digitos");
  Serial.print ("dia: DD, mes: MM, anyo: AAAA\t");
  Serial.println ("Termine con un '/' ");
  Serial.print ("2. Hora: Introduzca la hora: HH y minutos: MM");
  Serial.println ("Termine con un '/' ");
  Serial.print ("3. Alarmas:  Introduzca la hora: HH y minutos: MM en que debe dispararse la alarma de lunes a viernes ");
  Serial.println ("Termine con un '/' ");
  int nAjuste = 0;
  do {
    dataEntry = getEntry();
    int primerNumero = dataEntry[0] - '0';
    nAjuste = getConfirm(primerNumero, dataEntry, answer);
  }
  while (0 < nAjuste < 3);
  Serial.print ("Calendario :"); Serial.printf ("%d-%d-%d\n", dia, mes, anyo);
  Serial.print ("Reloj :"); Serial.printf ("%d:%d:%d\n", hora, minuto, segundo);
  Serial.print ("Alarma :"); Serial.printf ("%d:%d\n", alarmHora, alarmMinuto);

  intervalo = 1000; //milliseconds
  // select pinModes
  redPin = 9;
  greenPin = 10;
  bluePin = 11;
  buzzerPin = 3;
  switchPin = 2;
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  //free pins and switchPin are turned into Pull-up mode
  pinMode(!redPin && !greenPin && !bluePin && !buzzerPin, INPUT_PULLUP);
  //analog pins turned into pull-up mode too
  for (int r = A0; r <= A5; r++) {
    digitalWrite(r, HIGH);
    attachInterrupt(digitalPinToInterrupt(switchPin), Reset, CHANGE);
  }
  Timer1.initialize(1000000); //cada segundo
  Timer1.attachInterrupt(isr); 
  // initialize timer1, and set a 1 second interval
  // initialize Timer1
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  OCR1A = 15624;

  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);

  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);

  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
  sei();          // enable global interrupts

   /*Se supone que debo tener los ajustes hechos*/
  Serial.begin(9600); //Activo el monitor
  Serial.println ("Instrucciones para ajustes del reloj Rufus");
  Serial.println ("1. Calendario: Introduzca en este orden y con dos digitos");
  Serial.print ("dia: DD, mes: MM, anyo: AAAA\t");
  Serial.println ("Termine con un '/' ");
  Serial.print ("2. Hora: Introduzca la hora: HH y minutos: MM");
  Serial.println ("Termine con un '/' ");
  Serial.print ("3. Alarmas:  Introduzca la hora: HH y minutos: MM en que debe dispararse la alarma de lunes a viernes ");
  Serial.println ("Termine con un '/' ");
  nAjuste = 0;
  do {
    dataEntry = getEntry();
    int primerNumero = dataEntry[0] - '0';
    nAjuste = getConfirm(primerNumero, dataEntry, answer);
  }
  while (0 < nAjuste < 3);
  Serial.print ("Calendario :"); Serial.printf ("%d-%d-%d\n", dia, mes, anyo);
  Serial.print ("Reloj :"); Serial.printf ("%d:%d:%d\n", hora, minuto, segundo);
  Serial.print ("Alarma :"); Serial.printf ("%d:%d\n", alarmHora, alarmMinuto);
  attachInterrupt(2, Reset, FALLING);
}

void loop() {
  // If Alarm is set, sound

  digitalClockDisplay();

  Alarm.delay(0);

  Alarm.alarmRepeat(dowMonday, alarmHora, alarmMinuto, 10, Alarma);
  Alarm.alarmRepeat(dowTuesday, alarmHora, alarmMinuto, 10, Alarma);
  Alarm.alarmRepeat(dowWednesday, alarmHora, alarmMinuto, 10, Alarma);
  Alarm.alarmRepeat(dowThursday, alarmHora, alarmMinuto, 10, Alarma);
  Alarm.alarmRepeat(dowFriday, alarmHora, alarmMinuto, 10, Alarma); //Create an alarm that will call a function every week on a specific day at a particular time.

}
//Functions
void showTime() {
  Serial.print("Date:"); Serial.print(year()); Serial.print("/"); Serial.print(month()); Serial.print("/"); Serial.println(day());
  Serial.print("hour:"); Serial.print(hour()); Serial.print(":"); Serial.print(minute()); Serial.print(":"); Serial.println(second());
}
void Alarma() {
  // blink();
  buzzer(3, 127);
  Serial.print("Putas alarmas cojoneras!");

}
void noAlarma() {
  setColor(0, 0, 0);
  buzzer(buzzerPin, 0);
}

// Set colors. 255 is the maximum value of one color
void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
//Function
void blink() {
  //Apago todos los colores
  setColor(0, 0, 0);
  switch (flag) {
    case 0:
      setColor(255, 0, 0);
      break;
    case 1:
      setColor(0, 0, 0);
      break;
    case 2:
      setColor(0, 255, 0);
      break;
    case 3:
      setColor(0, 0, 0);
      break;
    case 4:
      setColor(0, 0, 255);
      break;
    case 5:
      setColor(0, 0, 0);
      break;
    default:
      setColor(0, 0, 0);
      break;
  }
}


//Function callback()
void isr()
{ k = k + 1;
  flag = k % 6;
  }

//Function that makes the buzzer sound
void buzzer(int pin, int cycle) {
  switch (flag) {
    case 0:
      analogWrite(pin, cycle);
    case 1:
      analogWrite(pin, 0);
    case 2:
      analogWrite(pin, cycle);
    case 3:
      analogWrite(pin, 0);
    case 4:
      analogWrite(pin, cycle);
    case 5:
      analogWrite(pin, 0);
  }

}

//Function light color
void LigthColor(int red, int green, int blue) {
  setColor(red, green, blue);
}
void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits)
{
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
