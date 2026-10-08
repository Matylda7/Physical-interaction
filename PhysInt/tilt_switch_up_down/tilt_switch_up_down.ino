#include <Mouse.h>

// Define digital pins for directions
const int UP_PIN = A0;
const int DOWN_PIN = A1;
//const int LEFT_PIN = 4;
//const int RIGHT_PIN = 5;

// Adjust mouse sensitivity (higher = faster cursor speed)
const int speed = 5; 

void setup() {
  // Initialize the pins as inputs with internal pull-up resistors
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
 // pinMode(LEFT_PIN, INPUT_PULLUP);
 // pinMode(RIGHT_PIN, INPUT_PULLUP);

  // Initialize mouse control
  Mouse.begin();
}

void loop() {
 // int xDistance = 0;
  int yDistance = 0;

  // Read tilt switches (LOW means the mercury is connecting the contacts)
  if (digitalRead(UP_PIN) == LOW)    yDistance = -speed;
  if (digitalRead(DOWN_PIN) == LOW)  yDistance = speed;
  //if (digitalRead(LEFT_PIN) == LOW)  xDistance = -speed;
 // if (digitalRead(RIGHT_PIN) == LOW) xDistance = speed;

  // Move the mouse if any switch is active
 /* if (xDistance != 0 || yDistance != 0) {
    Mouse.move(xDistance, yDistance, 0);
  }*/
  if (yDistance != 0) {
    Mouse.move(0, yDistance, 0);
  }

  // Small delay to prevent erratic movements
  delay(15); 
}