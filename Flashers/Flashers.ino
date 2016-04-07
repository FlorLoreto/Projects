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



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
