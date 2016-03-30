void blinkandBuzz() {
  //Apago todos los colores
  for (int i = 1; i < repeatTimes; ++i) {
    setColor(255, 0, 0);
    Alarm.delay(500);
    setColor(0, 0, 0);
    analogWrite(buzzerPin, dutyCycle);
    //Rojo
    Alarm.delay(250);
    analogWrite(buzzerPin, 0);
    Alarm.delay(500);
    //verde
    setColor(0, 255, 0);
    Alarm.delay(250);
    setColor(0, 0, 0);
    analogWrite(buzzerPin, dutyCycle);
    Alarm.delay(500);
    analogWrite(buzzerPin,  0);
    Alarm.delay(250);
    //azul
    setColor(0, 0, 255);
    Alarm.delay(500);
    analogWrite(buzzerPin, 0);
    Alarm.delay(250);
    setColor(0, 0, 0);
    analogWrite(buzzerPin, dutyCycle);
    Alarm.delay(250);


    Serial.print("me llaman. Voy al instante con mi bandera!  "); Serial.print(flag); Serial.println(second());
  } 
  noBlinkNoBuzz();
}
