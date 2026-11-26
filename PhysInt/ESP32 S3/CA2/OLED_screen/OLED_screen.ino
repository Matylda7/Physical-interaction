#include <Arduino.h>
#include <U8x8lib.h>
#include <Wire.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA );   // OLEDs without Reset of the Display

bool wasConnectedWifi = false;
bool isConnectedWifi = false;

bool wasConnectedBlynk = false;
bool isConnectedBlynk = false;


unsigned long bothConnectedTime = 0;
bool screenCleared = false;

void updateDisplay() {
  u8x8.clear();
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  // if offline show "Connecting" 
  if (!isConnectedWifi || !isConnectedBlynk) {
    u8x8.setCursor(0, 0);
    u8x8.print("Connecting...");
  }

  // Wi-Fi status on 2nd row
  u8x8.setCursor(0, 2);
  if (isConnectedWifi) {
    u8x8.print("Wi-Fi connected");
  } else {
    u8x8.print("Wi-Fi...");
  }

  // Blynk status on 4th row
  u8x8.setCursor(0, 4);
  if (isConnectedBlynk) {
    u8x8.print("Blynk connected");
  } else {
    u8x8.print("Blynk...");
  }
}

void setup(void) {
  u8x8.begin();
  u8x8.setFlipMode(1);   // Enable (1) and disbale (0) 180 degree rotation of the display content
  updateDisplay();
}

void loop(void) { 
  if (millis() > 3000) isConnectedWifi = true;
  if (millis() > 6000) isConnectedBlynk = true;

 //checking if connection state changed
  if (isConnectedWifi != wasConnectedWifi || isConnectedBlynk != wasConnectedBlynk) {
    wasConnectedWifi = isConnectedWifi;
    wasConnectedBlynk = isConnectedBlynk;
    screenCleared = false;
      
    updateDisplay();

    // If both are now connected, start the 10-second countdown
    if (isConnectedWifi && isConnectedBlynk) {
      bothConnectedTime = millis();
    }
  }

// after both have connected for 5sec, clear the screen
  if (isConnectedWifi && isConnectedBlynk && !screenCleared) {
    if (millis() - bothConnectedTime >= 5000) {
      u8x8.clear();
      screenCleared = true;
    }
  }
 
}

