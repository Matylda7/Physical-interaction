const int LDR_PIN = D2; 
const int BUZZER_PIN = D3; 
 
void setup() { 
  Serial.begin(115200); 
  analogReadResolution(12); 
} 
 
void loop() { 
  int light = analogRead(LDR_PIN); 
  int pitch = map(light, 2000, 3700, 200, 2000);   // frequency in hertz 
  int constrainedPitch = constrain(pitch, 200,2000);

  if (constrainedPitch < 1800) {
    tone(BUZZER_PIN, constrainedPitch);
  } else {
    noTone(BUZZER_PIN);
  }
   
  Serial.println(pitch); 
  delay(20); 
} 