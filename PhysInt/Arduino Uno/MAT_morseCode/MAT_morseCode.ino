/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/digital/Button/
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 12;  // the number of the pushbutton pin
const int ledPin = 2;    // the number of the LED pin

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    //digitalWrite(ledPin, HIGH);
    //delay(700);
    //digitalWrite(ledPin, LOW);
    MAT();
  } 
}
int delay1(){
  delay(200);
}
int delay2(){
  delay(1000);
}
int dot(){
  digitalWrite(ledPin, HIGH);
  delay1();
  digitalWrite(ledPin,LOW);
  delay1();
}
int dash(){
  digitalWrite(ledPin, HIGH);
  delay1();
  delay1();
  delay1();
  digitalWrite(ledPin,LOW);
  delay1();
}

int MAT(){
  //M
  dash();
  dash();
  delay2();
  //A
  dot();
  dash();
  delay2();
  //T
  dash();
  delay2();
  //Y
  dash();
  dot();
  dash();
  dash();
  delay2();
  //L
  dot();
  dash();
  dot();
  dot();
  delay2();
  //D
  dash();
  dot();
  dot();
  delay2();
  //A
  dot();
  dash();
  delay2();
}
