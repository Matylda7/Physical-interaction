#include <Mouse.h>
#include <Keyboard.h>

const int UP_PIN = A0;
const int DOWN_PIN = A1;
const int LEFT_PIN = A2;
const int RIGHT_PIN = A3;
const int CLICK_PIN = 7; 
const int ERASER_PIN = 4; 

// LED Toggle Button
const int LED_TOGGLE_PIN = 8;

// Rotary Encoder
const int encoder0PinA = 13;
const int encoder0PinB = 12;

// RGB LED Pins
const int redPin = 11;
const int greenPin = 9;
const int bluePin = 10;

const int speed = 3; 
bool eraserActive = false;

// LED State Tracking
bool ledsEnabled = true;
int lastToggleReading = HIGH;
unsigned long lastDebounceToggle = 0;

// Colors
const int colors[][3] = {
  {255, 255, 255},     // 0: Black
  {255, 0, 0},   // 1: Red
  {0, 255, 0},   // 2: Green
  {0, 0, 255},   // 3: Blue
  {255, 255, 0}, // 4: Yellow
  {0, 255, 255}, // 5: Cyan
  {255, 0, 255}, // 6: Magenta
};
const int numColors = 7;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 5; 

void setup() {
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(CLICK_PIN, INPUT_PULLUP);
  pinMode(ERASER_PIN, INPUT_PULLUP); 
  pinMode(LED_TOGGLE_PIN, INPUT_PULLUP);

  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
  Mouse.begin();
  Keyboard.begin();

//set initial color to black
  updateColorLED(encoder0Pos);
}

void loop() {
  //Rotary Encoder (Color Selector)
  int n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (millis() - lastDebounceTime > debounceDelay) {
      if (digitalRead(encoder0PinB) == LOW) {
        encoder0Pos--;
      } else {
        encoder0Pos++;
      }
      encoder0Pos = (encoder0Pos + numColors) % numColors;
      updateColorLED(encoder0Pos);
      Serial.println(encoder0Pos);
      
      lastDebounceTime = millis();
    }
  }
  encoder0PinALast = n;

  //LED Toggle Button 
  int toggleReading = digitalRead(LED_TOGGLE_PIN);
  if (toggleReading == LOW && lastToggleReading == HIGH) {
    if (millis() - lastDebounceToggle > 200) {
      ledsEnabled = !ledsEnabled;
      updateColorLED(encoder0Pos); 
      lastDebounceToggle = millis();
    }
  }
  lastToggleReading = toggleReading;

  //Mouse Movement via Tilt Switches
   int yDistance = 0;
   int xDistance = 0;
   if (digitalRead(UP_PIN) == HIGH)   yDistance = -speed;
   if (digitalRead(DOWN_PIN) == LOW)   yDistance = speed;
   if (digitalRead(LEFT_PIN) == HIGH) xDistance = -speed;
   if (digitalRead(RIGHT_PIN) == HIGH)xDistance = speed;
   if (yDistance != 0) Mouse.move(0, yDistance, 0);
   if (xDistance != 0) Mouse.move(xDistance, 0, 0);

  //Click Management
  if (digitalRead(CLICK_PIN) == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) Mouse.press(MOUSE_LEFT);
  } else {
    if (Mouse.isPressed(MOUSE_LEFT)) Mouse.release(MOUSE_LEFT);
  }

  //Eraser Tool Management
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

void updateColorLED(int index) {
  if (ledsEnabled) {
    analogWrite(redPin, colors[index][0]);
    analogWrite(greenPin, colors[index][1]);
    analogWrite(bluePin, colors[index][2]);
  } else {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
}