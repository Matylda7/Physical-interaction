/*
  Question 2 - Button with an external pull-down resistor
  ---------------------------------------------------------
  Wiring: as Question 1 (LED + 220 ohm resistor), plus a push button on
  Pin 2. One leg of the button goes to 5V; the other leg goes to Pin 2
  AND to GND through a 10 K ohm pull-down resistor.

  Because of the pull-down resistor, Pin 2 reads LOW when the button is
  NOT pressed, and HIGH when it IS pressed.

  Pressing the button spells out a first name in Morse code on the LED.
  Change the 'firstName' constant below to your own name.
*/

const int ledPin    = 2; 
const int buttonPin = 12;

const int dotTime   = 250;
const int dashTime  = dotTime * 3;
const int symbolGap = dotTime;
const int letterGap = dotTime * 3;

const char firstName[] = "MATYLDA"; // <-- change this to your own first name

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT); // external pull-down: LOW = not pressed, HIGH = pressed
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {  // button is pressed
    Serial.println("Printing name");
    playMorse(firstName);
    delay(1000); // short pause so one press plays the name once
  }
}

// --- Morse code helpers ---

void dot() {
  digitalWrite(ledPin, HIGH);
  delay(dotTime);
  digitalWrite(ledPin, LOW);
  delay(symbolGap);
}

void dash() {
  digitalWrite(ledPin, HIGH);
  delay(dashTime);
  digitalWrite(ledPin, LOW);
  delay(symbolGap);
}

// Morse patterns for A-Z, in alphabetical order as array
// const char* specifically means "a pointer to a char that
// shouldn't be modified through this pointer."
const char* morseAlphabet[26] = {
  ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",  "....",
  "..",   ".---", "-.-",  ".-..", "--",   "-.",   "---",  ".--.",
  "--.-", ".-.",  "...",  "-",    "..-",  "...-", ".--",  "-..-",
  "-.--", "--.."
};

// Plays one letter's dot/dash pattern
void playLetter(char letter) {
  letter = toupper(letter); //convert to uppercase
  if (letter < 'A' || letter > 'Z') return; // skip anything that isn't a letter
  /*
  See line below: letter - 'A'. In C++, a char is really just a number under the hood
  (its ASCII code), and 'A' is 65. So if letter is 'A', then letter - 'A' is 65 - 65 = 0;
  if letter is 'C', it's 67 - 65 = 2. 
  That arithmetic converts any uppercase letter directly into its position in the alphabet, zero-indexed
  */
  const char* pattern = morseAlphabet[letter - 'A'];
  for (int i = 0; pattern[i] != '\0'; i++) {
    if (pattern[i] == '.') dot();
    else dash();
  }
}

// Plays a whole word, with a gap between letters
void playMorse(const char* word) {
  for (int i = 0; word[i] != '\0'; i++) {
    playLetter(word[i]);
    delay(letterGap);
  }
}
