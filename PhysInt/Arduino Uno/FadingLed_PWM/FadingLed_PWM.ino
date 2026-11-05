const int redPin = 11;
const int bluePin = 9;
const int greenPin = 10;

int red = 0;
int blue = 0;
int green = 0;

int dimFactor = 20;
int fadeAmount = 50;

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
  int mappedPot = map(potentiometer, 0, 1023, 10, 255);
  Serial.print("Pot:");
  Serial.println(mappedPot);

  dimFactor = dimFactor + fadeAmount;
  Serial.println(dimFactor);

  if (dimFactor <= 0 || dimFactor >= 255){
    fadeAmount = fadeAmount * -1;
  }

  int baseRed = random(0, 256);
  int baseBlue = random(0, 256);
  int baseGreen = random(0, 256);
  
  red = baseRed - dimFactor;
  blue = baseBlue - dimFactor;
  green = baseGreen - dimFactor;

  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);


  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
  analogWrite(greenPin, green);


  Serial.print("Dim Factor: "); Serial.print(dimFactor);
  Serial.print(" | Red: "); Serial.print(red);
  Serial.print(" | Green: "); Serial.print(green);
  Serial.print(" | Blue: "); Serial.println(blue);


  delay(mappedPot +150);
}
