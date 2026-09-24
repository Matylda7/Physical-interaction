// Define the pins
const int potPin = A0;  // Center pin of the potentiometer goes to Analog A0
const int ledPin = 12;   // LED long leg goes to PWM Pin 9 (must have a ~ symbol next to the number)

void setup() {
  pinMode(ledPin, OUTPUT);  // Set the LED pin as an output
}

void loop() {
  // 1. Read the raw twisting value (0 to 1023)
  int potValue = analogRead(potPin); 
  
  // 2. Convert the value to the LED brightness range (0 to 255)
  int brightness = map(potValue, 0, 1023, 0, 255); 
  
  // 3. Write the intensity to the LED
  analogWrite(ledPin, brightness); 
  
  delay(10); // Tiny pause to keep things running smoothly
}
