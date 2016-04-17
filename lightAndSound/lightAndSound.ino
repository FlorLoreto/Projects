void lightAndSound() {
  k = k + 1; Serial.print ("  k "); Serial.println(k); Serial.print (";  flag "); Serial.print(flag);
  if (k <= 5) {
    digitalWrite(redPin, redInt);
    analogWrite(buzzPin, 127);
  }
  else if (k > 5 && k <= 6) {
    digitalWrite(redPin, redInt / 2); digitalWrite(greenPin, greenInt / 2);
    analogWrite(buzzPin, 0);
  }
  else if (k > 6 && k <= 11) {
    digitalWrite(greenPin, greenInt);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 34);
  }
  else if (k > 11 && k <= 13) {
    digitalWrite(greenPin, greenInt / 2); digitalWrite(bluePin, blueInt / 2);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 0);
  }
  else if (k > 13 && k <= 18) {
    digitalWrite(bluePin, greenInt);
    digitalWrite(greenPin, 0);
    analogWrite(buzzPin, 205);
  }
  else {
    digitalWrite(greenPin, 0);
    digitalWrite(bluePin, 0);
    digitalWrite(redPin, 0);
    analogWrite(buzzPin, 0);
    k = 0;
  }
  }
