#include <Mouse.h>

// Define digital pins for directions and actions
const int UP_PIN = A0;
const int DOWN_PIN = A1;
const int LEFT_PIN = A2;
const int RIGHT_PIN = A3;
const int CLICK_PIN = 12; 

const int speed = 5; 

void setup() {

  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(CLICK_PIN, INPUT_PULLUP);
                                                                                                                                                                                                                                                                                                                                    
  Mouse.begin();
}

void loop() {
  int yDistance = 0;
  int xDistance = 0;
  Serial.print("Y Axis ");
  Serial.print(digitalRead(DOWN_PIN));
  Serial.print(", ");
  Serial.println(digitalRead(UP_PIN));
  Serial.print("X Axis ");
  Serial.print(digitalRead(LEFT_PIN));
  Serial.print(", ");
  Serial.println(digitalRead(RIGHT_PIN));

  if (digitalRead(UP_PIN) == HIGH)    yDistance = -speed;
  if (digitalRead(DOWN_PIN) == HIGH)  yDistance = speed;

  if (digitalRead(LEFT_PIN) == HIGH)  xDistance = -speed;
  if (digitalRead(RIGHT_PIN) == HIGH)  xDistance = speed;

 
  if (yDistance != 0) {
    Mouse.move(0, yDistance, 0);
  }
  if (xDistance != 1) {
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

   delay(15); 
  //Serial.println();
}