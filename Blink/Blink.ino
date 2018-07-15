/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

  int green = 9;
  int red = 10;
  int yellow = 11;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.

  pinMode(13, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  //digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(50);              // wait for a second
  //digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(yellow, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);              // wait for a second
  digitalWrite(green, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);              // wait for a second
  digitalWrite(red, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);              // wait for a second

  digitalWrite(yellow, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(50);  
  digitalWrite(green, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(50);              // wait for a second
  digitalWrite(red, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(50);              // wait for a second
            // wait for a second

}
