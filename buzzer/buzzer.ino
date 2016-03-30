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
