#include <Encoder.h>

// Change these to the pins you are using
Encoder myEnc(8, 9);

const int redPin = 6;
const int greenPin = 3;
const int bluePin = 5;

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

long oldPosition = -999;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long newPosition = myEnc.read() / 4; // Divide by 4 to match physical detent clicks
  
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    
    // Wrap around the color index safely
    int colorIndex = (newPosition % numColors + numColors) % numColors;
    
    analogWrite(redPin, colors[colorIndex][0]);
    analogWrite(greenPin, colors[colorIndex][1]);
    analogWrite(bluePin, colors[colorIndex][2]);
    
    Serial.print("Color Index: ");
    Serial.println(colorIndex);
  }
}