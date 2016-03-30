
/* 
 DESCRIPTION
 ====================
 Simple example of the Bounce library that switches the debug LED when a button is pressed.
 */
// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce-Arduino-Wiring
#include <Bounce2.h>

#define switchPin 2// 
#define bluePin 11 //Blue 
int value=0;

// Instantiate a Bounce object
Bounce debouncer = Bounce(); 

void setup() {

  // Setup the button with an internal pull-up :
  pinMode(switchPin,INPUT_PULLUP);

  //Sets the pin and matches the internal state to that of the pin. Only attach the pin once you have done setting the pin up (for example internal pull-up).
  debouncer.attach(switchPin);
  debouncer.interval(5); // Sets the debounce time in milliseconds.

  //Setup the LED :
  pinMode(bluePin,OUTPUT);

}

void loop() {
  // Update the Bounce instance since we don`t use interrupts :
  debouncer.update();/*The update() method updates the object and returns true (1) if the pin state changed. False (0) if not. Only call update() once per loop().*/

 //Reads the updated pin state:
 value = debouncer.read();

  // Turn on or off the LED as determined by the state :
  if ( value == LOW ) {
    digitalWrite(bluePin, HIGH );
  } 
  else {
    digitalWrite(bluePin, LOW );
  }

}


