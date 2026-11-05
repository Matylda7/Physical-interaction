/*
 * Mouse Emulation Sketch for Arduino Leonardo
 * control button on Pin 8 starts and stops mouse emulation
 * mouse will move right and left on the x Axis.
 */

#include <Mouse.h>

const bool DEBUG = true;
const int potPin = A5;
const int ldrPin = A0;

const int buttonPin = 2;

//old and new pot Values
int potVal = -1;
int oldPotVal = -1;

//stores mapped ldrValues
int ldrNum = -1;
int lastLdr = -1;


int range = 5; //how fast the mouse moves each time
int xDistance = 0;
int multiplier = 1; //this reverses direction

void setup() {
  Serial.begin(9600);
  Mouse.begin();
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  //waits for the control button to go HI
  while (digitalRead(buttonPin) == HIGH) {
    Serial.print("==Waiting===, ");
    Serial.println(digitalRead(buttonPin));
    // do nothing until buttonpPin  goes low
    delay(500);
  }
  
  int potValue = analogRead(potPin);
  int ldrValue = analogRead(ldrPin);

  potVal = map(potValue, 0, 1023, -10, 10);  
  ldrNum = map(ldrValue, 600, 900, -10, 10);  



 
  if (DEBUG) {
    Serial.print("potVal: ");
    Serial.print(potVal);
    Serial.print(", oldPotVal: ");
    Serial.print(oldPotVal);
    Serial.print(", ldrNum: ");
    Serial.print(ldrNum);
    Serial.print(", multiplier: ");
    Serial.print(multiplier);
    Serial.print(", lastLdr: ");
    Serial.println(lastLdr);
  }

  //only update if pot value changed
  if ( potVal != oldPotVal) {
     if (potVal - oldPotVal > 0) {
      Serial.println("===Right direction.");
      multiplier = 1;
     } else {
      Serial.println("===Left direction.");
      multiplier = -1;
     }
  }

    if (DEBUG) {
    Serial.print("potVal: ");
    Serial.print(potVal);
    Serial.print(", oldPotVal: ");
    Serial.print(oldPotVal);
    Serial.print(", ldrNum: ");
    Serial.print(ldrNum);
    Serial.print(", multiplier: ");
    Serial.print(multiplier);
    Serial.print(", xDistance: ");
    Serial.print(xDistance);
    Serial.print(", lastLdr: ");
    Serial.println(lastLdr);
  }


  xDistance = multiplier * range;
  Mouse.move(xDistance, 0,0);
  
 
  oldPotVal = potVal; //store current value in lastKey
  lastLdr = ldrNum;  //store current ldrvalue in lastLdr

                          // Release previous key
  delay(100);             // debounce and prevent flooding
}
