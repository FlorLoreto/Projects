//Writes on LCD using only 4 pins
#include <Time.h>
#include <TimeLib.h>

/*
LiquidCrystal Library - Hello World
Demonstrates the use of a 16 × 2 LCD display.
http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

#include <LiquidCrystal.h> // include the library code
//constants for the number of rows and columns in the LCD
const int numRows = 2;
const int numCols = 16;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);//LiquidCrystal(RS, (R/W), Enable, d4, d5, d6, d7) . R/W is optional.
void setup()
{
  setTime(16,42,15,14,04,2015);
lcd.begin(numCols, numRows);//Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of 
// the display. begin() needs to be called before any other LCD library commands.
lcd.print("Esta es la hora: "); // Print a message to the LCD.
}
void loop()
{
// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
lcd.setCursor(0, 1); //lcd.setCursor(col, row): Position the LCD cursor; that is, set the location at which subsequent text written to the LCD will be displayed.
// print the number of seconds since reset:
lcd.print("\t\t\t ");lcd.print(hour());lcd.print(":");lcd.print(minute());lcd.print(":");lcd.print(second());lcd.print(" \t\t\t");
}
