#include <ESP32Servo.h>

const int POT_PIN = D0;
const int SERVO_PIN = D2;

int currentPos = 0;
int potValue = 0;
Servo servo;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  servo.setPeriodHertz(50);              // standard servo frequency
  servo.attach(SERVO_PIN, 500, 2400);   // pulse range in microseconds
  servo.write(currentPos);
  delay(500);
}

void loop() {
  potValue = analogRead(POT_PIN);
  moveServo(potValue);
}

void moveServo(int potValue){
  int targetPos = map(potValue, 0, 1023, 0, 179);

  if (targetPos > currentPos){
  Serial.println("moving right");
    for (int pos = currentPos; pos <= targetPos; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      servo.write(pos);    // tell servo to go to position in variable 'pos
      delay(15);             // waits 15ms for the servo to reach the position
    }
  currentPos = targetPos;

  } else if (targetPos < currentPos){
    Serial.println("moving left");
    for (int pos = currentPos; pos >= targetPos; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo.write(pos);    // tell servo to go to position in variable 'pos'
      delay(15);             // waits 15ms for the servo to reach the position

    }
    currentPos = targetPos;
  }
  
}
  