// Piranha RGB LED: smooth rainbow fade
// Board: Arduino Uno
//
// Wiring:
//   LED red   -> 220 ohm resistor -> pin 9
//   LED green -> 220 ohm resistor -> pin 10
//   LED blue  -> 220 ohm resistor -> pin 11
//   LED common leg -> 5V (common anode) or GND (common cathode)
//
// How it works:
//   The rainbow is split into three stages, each 256 steps long:
//     Stage 1: red   fades to green  (passing through yellow)
//     Stage 2: green fades to blue   (passing through cyan)
//     Stage 3: blue  fades to red    (passing through purple)
//   That makes 768 steps in total, and then it starts again.

const int RED_PIN   = 9;    // LED pins must be PWM pins (marked ~)
const int GREEN_PIN = 10;
const int BLUE_PIN  = 11;
int potValue = 0;

int redLevel = 0;
int blueLevel = 0;

// Change this to match your LED:
// true  = common anode   (common leg connected to 5V)
// false = common cathode (common leg connected to GND)
const bool COMMON_ANODE = false;


int FADE_DELAY = 10;
void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  potValue = analogRead(A2);
  fadeColour(potValue);

  delay(FADE_DELAY);
}

// Works out the colour for a position in the rainbow (0 to 510)
// and sends it to the LED.
void fadeColour(int pos) {

  redLevel = map(pos, 0, 1023, 0, 255);
  blueLevel = 255 - redLevel;

  if (COMMON_ANODE) {
    redLevel   = 255 - redLevel;
    blueLevel  = 255 - blueLevel;
  }
  analogWrite(RED_PIN, redLevel);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN, blueLevel);
  Serial.println(pos);
}


