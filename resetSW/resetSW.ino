//ESTE PROGRAMA REARRANCA AL PULSAR EL SWITCH EN PIN N 2
#include <avr/wdt.h>//NECESITAMOS EL WATCHDOG
const int ledPin=13;
const int buzzerPin=3;
const int switchPin=2;
int state;
//ISR PARA PULSACION DE BOTON
void swreboot()
{
  wdt_enable(WDTO_250MS);
  while(1);
}

void setup() {
  // put your setup code here, to run once:
pinMode(ledPin,OUTPUT);
pinMode(buzzerPin,OUTPUT);
pinMode(switchPin,INPUT_PULLUP);
//pinMode(switchPin,OUTPUT);
attachInterrupt(digitalPinToInterrupt(switchPin), swreboot, CHANGE);



Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(buzzerPin, 56);
digitalWrite(ledPin, HIGH);
//digitalWrite(switchPin,HIGH);
state = digitalRead(switchPin);
Serial.print("estado del switch ");Serial.println (state);
//swreboot();
} 
                                                                                                                                                                                                                                                                                                                                       
