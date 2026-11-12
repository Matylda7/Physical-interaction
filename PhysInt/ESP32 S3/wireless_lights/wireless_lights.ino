#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// ---- Settings ----
const char *WIFI_SSID = "";
const char *WIFI_PASS = "";

// Name shown in the router admin page and used for http://<name>.local
// Letters, digits and hyphens only. Make it unique for each board.
const char *HOSTNAME = "xiao-led-01";

const int LED_PINS[3] = {D1, D4, D5};

// ---- Objects ----
WebServer server(80);

// ---- Slider state ----
int ledCount = 0;             // number of LEDs held on by the slider (0 to 3)

// Show the slider setting: the first ledCount LEDs on, the rest off
void showSlider() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PINS[i], i < ledCount ? HIGH : LOW);
  }
}

void setAll(bool on) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PINS[i], on ? HIGH : LOW);
  }
}

// ---- Sequence state ----
bool running = false;
int step = 0;
unsigned long lastStep = 0;
const unsigned long STEP_MS = 150;
// Chase 1,2,3,2,1 (5 steps) then three flashes (6 steps: on, off, on, off, on, off)
const int CHASE_PATTERN[5] = {0, 1, 2, 1, 0};
const int CHASE_STEPS = 5;
const int FLASH_STEPS = 6;
const int TOTAL_STEPS = CHASE_STEPS + FLASH_STEPS;

//this is the webpage that the ESP32 serves
const char PAGE[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>LED Control</title>
<style>
  body { font-family: system-ui, sans-serif; display: flex; flex-direction: column;
         align-items: center; justify-content: center; min-height: 100vh; margin: 0;
         background: #14161a; color: #eee; }
  button { font-size: 1.4rem; padding: 1rem 2.5rem; border: 0; border-radius: 999px;
           background: #3b82f6; color: #fff; cursor: pointer; }
  button:disabled { background: #555; cursor: default; }
  input[type=range] { width: 260px; margin-top: 0.8rem; }
  .hint { font-size: 0.9rem; color: #999; }
  p { margin: 1rem 0 0; min-height: 1.5em; }
</style>
</head>
<body>
  <h1>LED Control</h1>
  <button id="go">Light up</button>
  <p id="msg"></p>
  <hr style="width:260px;border-color:#333;margin:1.5rem 0 1rem">
  <label for="leds">LEDs lit: <strong id="count">0</strong></label>
  <input type="range" id="leds" min="0" max="3" step="1" value="0">
  <p class="hint">0 = off, 1 to 3 = number of LEDs lit</p>
<script>
  const btn = document.getElementById('go');
  const msg = document.getElementById('msg');
  btn.addEventListener('click', async () => {
    btn.disabled = true;
    msg.textContent = 'Running...';
    try {
      const r = await fetch('/run');
      msg.textContent = await r.text();
    } catch (e) {
      msg.textContent = 'Could not reach the board.';
    }
    setTimeout(() => { btn.disabled = false; msg.textContent = ''; }, 2000);
  });

  const slider = document.getElementById('leds');
  const count = document.getElementById('count');
  slider.addEventListener('input', () => { count.textContent = slider.value; });
  slider.addEventListener('change', async () => {
    try { await fetch('/leds?n=' + slider.value); }
    catch (e) { msg.textContent = 'Could not reach the board.'; }
  });
</script>
</body>
</html>
)HTML";

void updateSequence() {
  if (!running) return;
  if (millis() - lastStep < STEP_MS) return;
  lastStep = millis();

  if (step < CHASE_STEPS) {
    setAll(false);
    digitalWrite(LED_PINS[CHASE_PATTERN[step]], HIGH);
  } else if (step < TOTAL_STEPS) {
    bool on = ((step - CHASE_STEPS) % 2 == 0);
    setAll(on);
  } else {
    // Finished: return to the slider setting
    showSlider();
    running = false;
    return;
  }
  step++;
}

void handleRoot() {
  server.send_P(200, "text/html", PAGE);
}

void handleRun() {
  if (running) {
    server.send(200, "text/plain", "Already running.");
  } else {
    running = true;
    step = 0;
    lastStep = 0;
    server.send(200, "text/plain", "Sequence started.");
  }
}

void handleLeds() {
  int n = server.hasArg("n") ? server.arg("n").toInt() : 0;
  ledCount = constrain(n, 0, 3);
  if (!running) showSlider();
  server.send(200, "text/plain", String(ledCount));
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 3; i++) pinMode(LED_PINS[i], OUTPUT);
  setAll(false);

  WiFi.mode(WIFI_STA); // setting wifi
  WiFi.setHostname(HOSTNAME);  //passing in host name  // must come before WiFi.begin()
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nOpen http://");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(HOSTNAME)) {
    Serial.print("or http://");
    Serial.print(HOSTNAME);
    Serial.println(".local");
  }
// defining routes
  server.on("/", handleRoot);
  server.on("/run", handleRun);
  server.on("/leds", handleLeds);
  server.begin();
}

void loop() {
  //runs the whole time as its waiting for user input to start
  server.handleClient();
  updateSequence();
}