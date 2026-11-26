#include <Arduino.h>
#include <U8x8lib.h>
#include <Wire.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA );   // OLEDs without Reset of the Display

bool wasConnectedWifi = false;
bool isConnectedWifi = false;

bool wasConnectedBlynk = false;
bool isConnectedBlynk = false;

void setup(void) {
  u8x8.begin();
  u8x8.setFlipMode(1);   // Enable (1) and disbale (0) 180 degree rotation of the display content
  showConnectingWifi();
  showConnectingBlynk();
}

void loop(void) { 
  if (millis() > 3000) {
    isConnectedWifi = true; 
  }
  if (millis() > 6000) {
    isConnectedBlynk = true; 
  }
  //first time connecting
  if (isConnectedWifi && !wasConnectedWifi) {
    showConnectedWifi();
    wasConnectedWifi = true;
  }

  if (isConnectedBlynk && !wasConnectedBlynk) {
    showConnectedBlynk();
    wasConnectedBlynk = true;
  }
  
  //Check if JUST disconnected
  else if (!isConnectedWifi && wasConnectedWifi) {
    showConnectingWifi();
    wasConnectedWifi = false; 
  }

  else if (!isConnectedBlynk && wasConnectedBlynk) {
    showConnectingBlynk();
    wasConnectedBlynk = false; 
  }
 
}

void showConnectingWifi(){
  u8x8.clear();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 0);
  u8x8.println("Connecting Wi-Fi...");
}

void showConnectingBlynk(){
  u8x8.clear();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 0);
  u8x8.println("Connecting Blynk...");
}


void showConnectedWifi(){
  u8x8.clear();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 0);
  u8x8.println("Wi-Fi connected");

  delay(10000);
  u8x8.clear();

}
void showConnectedBlynk(){
  u8x8.clear();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 0);
  u8x8.println("Blynk connected");

  delay(10000);
  u8x8.clear();
}