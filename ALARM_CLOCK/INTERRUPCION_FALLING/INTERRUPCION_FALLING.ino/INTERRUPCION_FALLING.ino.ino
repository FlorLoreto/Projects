#include <TimeLib.h>
#include <TimeAlarms.h>
#include <StopWatch.h>
//Handles the intrrupt when pressing the push button.
// Definition of interrupt names
int switchPin = 2;
const int buzzPin = 6;
// We need to declare the data exchange
// variable to be volatile - the value is
// read from memory.
int volatile value=0;
StopWatch reloj(StopWatch::SECONDS);
StopWatch relox(StopWatch::SECONDS);
int alma = 10;
int alarmHora = 0;
int alarmSegundo = 60;
int alarmMinuto = 0;
int Hora = 10;
int Segundo = 0;
int Minuto = 0;
int alMinutoDia;
long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

//============  service request function ===================
void Alarma() {
   
   value = 1;//returns value=1
  }
//============= buzzing function ========================
void buzzing() {
  reloj.start();
    while (reloj.elapsed() < 15 && value == 1) {
    analogWrite(buzzPin, 127);
     Serial.printf("Alarma!!!!\n");
   }
  analogWrite(buzzPin, 0);
  reloj.reset();
}
//--------------  setup ------------------------------------
void setup() {
  reloj.start();
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);//Open es HIGH
  value = digitalRead(switchPin);
  attachInterrupt( digitalPinToInterrupt(switchPin), debounceInterrupt, FALLING); //INT0  Iis Pin 2.
  setTime(Hora, Minuto,  Segundo, 15, 4, 2015);
  
 Alarm.alarmRepeat(alarmHora, alarmMinuto,  alarmSegundo, Alarma);
 }
//------------------  main -----------------------------------
void loop() {
  Serial.printf("Value is %d and time \n",value,reloj.elapsed());
  // put your main code here, to run repeatedly:
  if (value == 1) {
    Serial.printf("Value is %d\n",value);
    buzzing();
  } else {
    //Serial.printf("Value LOW! %d\n",value);
    analogWrite(buzzPin, 0);
  }
  Alarm.delay(12);}
// ==================  Install the interrupt routine ======================
//-------------------- debounce -------------------------------------------
void debounceInterrupt() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) {

    ServicioBoton();
    last_micros = micros();
  }

}
//---------------------  service routine ------------------------------------
void ServicioBoton() {
  // check the value again - since it takes some time to
  // activate the interrupt routine, we get a clear signal.
  value = digitalRead(switchPin); Serial.printf("Service boton\n"); Serial.printf("Value! %d\n", value);

  //if (Alarm.isTriggered()
 
}

