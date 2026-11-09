const int LED_PIN = LED_BUILTIN;  // GPIO21, active low 
const int BUTTON_PIN = 0;         // BOOT button, reads LOW when pressed 
bool ledOn = false;

void setup() { 
  pinMode(LED_PIN, OUTPUT); 
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  Serial.begin(115200); 
} 
 
void loop() { 
  int reading = digitalRead(BUTTON_PIN);

  if (reading == LOW) {
    ledOn = !ledOn;
  }

  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);   // LED on 
  if (ledOn) {
    Serial.println(1);
  } else {
    Serial.println(2);
  }
 
} 
