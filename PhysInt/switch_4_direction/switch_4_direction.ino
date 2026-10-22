#include <Mouse.h>
#include <Keyboard.h>

const int UP_PIN = A0;
//const int DOWN_PIN = A1;
const int LEFT_PIN = A2;
const int RIGHT_PIN = A3;
const int CLICK_PIN = 12; 
const int ERASER_PIN = 11; 

const int speed = 3; 

bool eraserActive = false;

void setup() {
  pinMode(UP_PIN, INPUT_PULLUP);
  //pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(CLICK_PIN, INPUT_PULLUP);
  pinMode(ERASER_PIN, INPUT_PULLUP); 
                                                           
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  int yDistance = 0;
  int xDistance = 0;

  if (digitalRead(UP_PIN) == HIGH)    yDistance = -speed;
  //if (digitalRead(DOWN_PIN) == HIGH)  yDistance = speed;

  if (digitalRead(LEFT_PIN) == HIGH)  xDistance = -speed;
  if (digitalRead(RIGHT_PIN) == HIGH) xDistance = speed;

  if (yDistance != 0) {
    Mouse.move(0, yDistance, 0);
  }
  if (xDistance != 0) {
    Mouse.move(xDistance, 0, 0);
  }

  
  if (digitalRead(CLICK_PIN) == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  } else {
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  if (digitalRead(ERASER_PIN) == LOW) {
    if (!eraserActive) {
      Keyboard.press('e');
      eraserActive = true;
    }
  } else {
    if (eraserActive) {
      Keyboard.release('e');
      eraserActive = false;
    }
  }

  delay(15); 
}