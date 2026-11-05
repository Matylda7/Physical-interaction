
const int redLight = 11;
const int blueLight = 9;
const int greenLight = 10;
const int buttonPin = 2;

int buttonState;  
int lastButtonState = HIGH;

const int colors[10][3] = {
  {255, 0, 0},     // 0: Red
  {255, 80, 0},    // 1: Orange
  {0, 0, 255},     // 2: Blue
  {255, 255, 0},   // 3: Yellow
  {0, 255, 0},     // 4: Green
  {0, 255, 255},   // 5: Cyan
  {128, 0, 128},   // 6: Purple
  {255, 105, 180}, // 7: Pink
  {0, 128, 128},   // 8: Teal
  {255, 255, 255}  // 9: White
};

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(greenLight, OUTPUT);
  pinMode(redLight, OUTPUT);
  pinMode(blueLight, OUTPUT);
  Serial.begin(9600);

  randomSeed(analogRead(A0));
}

void loop() {
  // put your main code here, to run repeatedly:

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        getColor();
      }
    }
  }
  lastButtonState = reading;
  
}


void getColor(){
  int currentColor = random(0,10);
  analogWrite(redLight, colors[currentColor][0]);
  analogWrite(greenLight, colors[currentColor][1]);
  analogWrite(blueLight, colors[currentColor][2]);
  Serial.println(currentColor);
}