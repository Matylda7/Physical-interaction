// first
const int encoder0PinA = 8;
const int encoder0PinB = 9;

const int redPin = 6;
const int greenPin = 3;
const int bluePin = 5;

int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

const int colors[][3] = {
  {255, 0, 0},   // Red
  {0, 255, 0},   // Green
  {0, 0, 255},   // Blue
  {255, 255, 0}, // Yellow
  {0, 255, 255}, // Cyan
  {255, 0, 255}, // Magenta
  {255, 255, 255}// White
};
const int numColors = 7;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 5; // Minimum milliseconds between valid steps

void setup() {
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  n = digitalRead(encoder0PinA);
  
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    // Check if enough time has passed to ignore bounce noise
    if (millis() - lastDebounceTime > debounceDelay) {
      if (digitalRead(encoder0PinB) == LOW) {
        encoder0Pos--;
      } else {
        encoder0Pos++;
      }
      
      encoder0Pos = (encoder0Pos + numColors) % numColors;
      
      analogWrite(redPin, colors[encoder0Pos][0]);
      analogWrite(greenPin, colors[encoder0Pos][1]);
      analogWrite(bluePin, colors[encoder0Pos][2]);
      
      Serial.print("Color Index: ");
      Serial.println(encoder0Pos);
      
      lastDebounceTime = millis();
    }
  }
  encoder0PinALast = n;
}