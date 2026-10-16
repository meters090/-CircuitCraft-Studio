/*
 * ============================================================================
 *  SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (ESP8266, non-blocking version)
 * ----------------------------------------------------------------------------
 *  Board      : NodeMCU v2 / Wemos D1 mini
 *  Module     : 1-channel 5 V relay board
 *  Behaviour  : millis() based toggling — no delay(), so WiFi / MQTT / web
 *               server code can run in loop() without being blocked.
 *  Relay      : toggles every 2000 ms (2 s ON, 2 s OFF → 4 s period).
 *
 *  Wiring: Relay IN -> D1 (GPIO5), VCC -> 5V, GND -> GND
 * ============================================================================
 */

#define RELAY_PIN        5      // D1 (GPIO5)
#define RELAY_ACTIVE_LOW true

const unsigned long INTERVAL_MS = 2000UL;   // 2 seconds

bool     relayState = false;
unsigned long lastToggle = 0;

void setRelay(bool on) {
  relayState = on;
  digitalWrite(RELAY_PIN, (on ^ RELAY_ACTIVE_LOW) ? HIGH : LOW);
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  setRelay(false);
  lastToggle = millis();
}

void loop() {
  if (millis() - lastToggle >= INTERVAL_MS) {
    lastToggle += INTERVAL_MS;
    setRelay(!relayState);
  }

  // ... WiFi / MQTT / server handling goes here, never blocked ...
}
