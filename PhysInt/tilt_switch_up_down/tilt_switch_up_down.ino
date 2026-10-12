#include <Mouse.h>

// Define digital pins for directions and actions
const int UP_PIN = A0;
const int DOWN_PIN = A1;
const int CLICK_PIN = 2; // New pin for your click button

// Adjust mouse sensitivity (higher = faster cursor speed)
const int speed = 5; 

void setup() {
  // Initialize the pins as inputs with internal pull-up resistors
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(CLICK_PIN, INPUT_PULLUP); // Initialize the click pin

  // Initialize mouse control
  Mouse.begin();
}

void loop() {
  int yDistance = 0;

  // Read tilt switches (LOW means the mercury is connecting the contacts)
  if (digitalRead(UP_PIN) == LOW)    yDistance = -speed;
  if (digitalRead(DOWN_PIN) == LOW)  yDistance = speed;

  // Move the mouse if any switch is active
  if (yDistance != 0) {
    Mouse.move(0, yDistance, 0);
  }

  // Handle holding down and releasing the mouse button
  if (digitalRead(CLICK_PIN) == LOW) {
    // If the physical button is held down, hold down the left mouse click
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  } else {
    // If the physical button is released, release the left mouse click
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  // Small delay to prevent erratic movements
  delay(15); 
}