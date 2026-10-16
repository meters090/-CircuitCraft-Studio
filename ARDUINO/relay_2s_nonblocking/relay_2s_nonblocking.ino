/*
 * ============================================================================
 *  SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (non-blocking version)
 * ----------------------------------------------------------------------------
 *  Board      : Arduino Uno / Nano / Mega
 *  Module     : 1-channel 5 V relay board
 *  Behaviour  : Uses millis() instead of delay(), so loop() stays free to
 *               read sensors, run serial, etc. Relay still toggles every 2 s.
 *
 *  Wiring:  Relay IN -> pin 7, VCC -> 5V, GND -> GND
 *           Most 1-ch boards are ACTIVE-LOW — set RELAY_ACTIVE_LOW to match.
 * ============================================================================
 */

#define RELAY_PIN        7
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
  // Toggle the relay every INTERVAL_MS without blocking.
  if (millis() - lastToggle >= INTERVAL_MS) {
    lastToggle += INTERVAL_MS;
    setRelay(!relayState);
  }

  // ... other non-blocking tasks can run here ...
}
