/*
  RGB LED
*/
//include libraries
#include <Time.h>
#include <TimerOne.h>
#include <TimeAlarms.h>
//declare variables
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
//El tiempo de encendido de cada color en milisegundos:
volatile int flag;//Volatile directs the compiler to load the variable from RAM and not from a storage register, which is a temporary memory location 
//where program variables are stored and manipulated. Under certain conditions, the value for a variable stored in registers can be inaccurate.
int k = 0;
int bandera=0;
unsigned int m=0;
// Set colors. 255 is the maximum value of one color
void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
//Function callback()
void callback()
{
  flag = k % 6;
  k ++;
  //0: red
  //1:green
  //2:blue
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
      bandera=flag;
      k=0;
     break;
    default:
      setColor(0, 0, 0);
      break;
  }
  }

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Timer1.initialize(100000);         // initialize timer1, and set a usecond period
  Timer1.attachInterrupt(callback);
  Serial.begin(9600);// attaches callback() as a timer overflow interrupt
}
void loop()
{ 
blink();

Serial.print("");Serial.println(k);
}
//Functions




