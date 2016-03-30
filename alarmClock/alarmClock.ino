//This sketch will handle an Alarm Clock
//import libraries
//include libraries
#include <Time.h>
#include <TimerOne.h>
#include <TimeAlarms.h>
// 1. Variables declaration
int semDia;// Day of the week, Sunday is day 1
int dia;//Day
int mes; //Month
int anyo;//Year
int hora;//Hour
int minutos;//Minutes
int redPin;//Digital pin for red ligth
int greenPin;//Digital pin for green ligth
int bluePin;//Digital pin for blue ligth
int buzzerPin;//Digital pin for buzzer
int blinkRate;//Milliseconds the ligth is on or off
int pitchCycle;//Duty cycle of the PWM
int switchPin;//Digital pin to check the switch state
int alarmaHora;//Alarm hour
int alarmaMinutos;//Alarm minutes
volatile int flag;
int k;
unsigned long interval;
long unsigned previousMillis;
long unsigned currentMillis;


// Alarm is always programmed from Monday (weekday 2) to Friday (weekday 6)
void setup() {
  // put your setup code here, to run once:
  dia = 28;
  mes = 3;
  anyo = 2016;
  hora = 18;
  minutos = 27;
  alarmaHora=18;
  alarmaMinutos=27;
  redPin = 9;
  greenPin = 10;
  bluePin = 11;
  blinkRate = 1000;
  buzzerPin = 3;
  pitchCycle = 127;
  switchPin = 2;
  k = 0;
  
  interval = 1000; //milliseconds
  // select pinModes
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  //free pins and switchPin are turned into Pull-up mode
  //pinMode(!redPin && !greenPin && !bluePin && !buzzerPin, INPUT_PULLUP);
  //analog pins turned into pull-up mode too
 /* for (int r = A0; r <= A5; r++) {
    digitalWrite(r, HIGH);
  }*/
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

//  Timer1.attachInterrupt(callback); // attaches callback() as a timer overflow interrupt
  Serial.begin(9600);
  //LigthColor(255,0,0);
  setTime(hora, minutos, 0, dia, mes, anyo);
  semDia = weekday();
 }

void loop() {
  // If Alarm is set, sound
  
  digitalClockDisplay();
  
  Alarm.delay(0);
  
  
  Alarm.alarmRepeat(dowMonday, alarmaHora, alarmaMinutos, 10, Alarma);
  Alarm.alarmRepeat(dowTuesday, alarmaHora, alarmaMinutos, 10, Alarma);
  Alarm.alarmRepeat(dowWednesday, alarmaHora, alarmaMinutos, 10, Alarma);
  Alarm.alarmRepeat(dowThursday, alarmaHora, alarmaMinutos, 10, Alarma);
  Alarm.alarmRepeat(dowFriday, alarmaHora, alarmaMinutos, 10, Alarma); //Create an alarm that will call a function every week on a specific day at a particular time.
 
  // "dayofweek" can be dowSunday, dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, or dowSaturday.
 /* Alarm.alarmRepeat(dowMonday, alarmaHora, alarmaMinutos, 0, noAlarma);
  Alarm.alarmRepeat(dowTuesday, alarmaHora, alarmaMinutos, 0, noAlarma);
  Alarm.alarmRepeat(dowWednesday, alarmaHora, alarmaMinutos, 0, noAlarma);
  Alarm.alarmRepeat(dowThursday, alarmaHora, alarmaMinutos, 0, noAlarma);
  Alarm.alarmRepeat(dowFriday, alarmaHora, alarmaMinutos, 0, noAlarma);*/
  /*currentMillis = millis();
  if ((millis() - previousMillis) >= interval)
  {
   showTime();
   previousMillis = currentMillis;
  }*/
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
ISR(TIMER1_COMPA_vect)
{ int x=second();
  k = k + 1;
  flag = k % 6;
  //0: red
  //1:green
  //2:blue
  Serial.print("Coitus interruptus! at"); Serial.println(x);  

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
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
