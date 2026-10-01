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

const int RED_PIN   = 8;    // LED pins must be PWM pins (marked ~)
const int GREEN_PIN = 12;
const int BLUE_PIN  = 13;

// Change this to match your LED:
// true  = common anode   (common leg connected to 5V)
// false = common cathode (common leg connected to GND)
const bool COMMON_ANODE = true;

// Time between steps in milliseconds.
// 10 gives one full rainbow roughly every 8 seconds.
// Smaller = faster, larger = slower.
const int FADE_DELAY = 10;

int position = 0;   // where we are in the rainbow: 0 to 767

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  showRainbowColour(position);

  position = position + 1;
  if (position > 767) {
    position = 0;     // back to the start of the rainbow
  }

  delay(FADE_DELAY);
}

// Works out the colour for a position in the rainbow (0 to 767)
// and sends it to the LED.
void showRainbowColour(int pos) {
  int red, green, blue;

  if (pos < 256) {
    // Stage 1: red to green
    red   = 255 - pos;
    green = pos;
    blue  = 0;
  }
  else if (pos < 512) {
    // Stage 2: green to blue
    int step = pos - 256;   // count from 0 again within this stage
    red   = 0;
    green = 255 - step;
    blue  = step;
  }
  else {
    // Stage 3: blue to red
    int step = pos - 512;
    red   = step;
    green = 0;
    blue  = 255 - step;
  }

  setColour(red, green, blue);
}

// Sets the LED colour using brightness values from 0 (off) to 255 (full)
void setColour(int red, int green, int blue) {
  // A common anode LED works "upside down": LOW means on.
  // So we flip the values before sending them to the pins.
  if (COMMON_ANODE) {
    red   = 255 - red;
    green = 255 - green;
    blue  = 255 - blue;
  }
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
