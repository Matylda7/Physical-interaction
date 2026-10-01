const int redPin = 11;
const int bluePin = 9;
const int greenPin = 10;

int red = 0;
int blue = 0;
int green = 0;

int dimFactor = 0;
int fadeAmount = 20;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  randomSeed(analogRead(A0));
}

void loop() {

  // put your main code here, to run repeatedly:
  int potentiometer = analogRead(A2);
  int mappedPot = map(potentiometer, 0, 1023, 5, 50);
  Serial.print("Pot:");
  Serial.println(mappedPot);

  dimFactor = dimFactor + fadeAmount;
  Serial.println(dimFactor);

  if (dimFactor <= 0 || dimFactor >= 255){
    fadeAmount = fadeAmount * -1;
  }

  red += random(-15, 16);
  blue += random(-15, 16);
  green += random(-15, 16);

  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);

  int finalRed   = constrain(red - dimFactor, 0, 255);
  int finalGreen = constrain(green - dimFactor, 0, 255);
  int finalBlue  = constrain(blue - dimFactor, 0, 255);


  analogWrite(redPin, finalRed);
  analogWrite(bluePin, finalBlue);
  analogWrite(greenPin, finalGreen);


  Serial.print("Dim Factor: "); Serial.print(dimFactor);
  Serial.print(" | Red: "); Serial.print(red);
  Serial.print(" | Green: "); Serial.print(green);
  Serial.print(" | Blue: "); Serial.println(blue);


  delay(mappedPot);
}
