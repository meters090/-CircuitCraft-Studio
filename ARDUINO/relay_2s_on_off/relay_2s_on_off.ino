/*
 * ============================================================================
 *  SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (blocking version)
 * ----------------------------------------------------------------------------
 *  Board      : Arduino Uno / Nano / Mega (Arduino AVR core)
 *  Module     : 1-channel 5 V relay board
 *  Behaviour  : loop forever →
 *                 relay ON  → wait 2000 ms
 *                 relay OFF → wait 2000 ms
 *
 *  Wiring
 *    Relay IN  -> pin 7 (change RELAY_PIN below)
 *    Relay VCC -> 5V
 *    Relay GND -> GND
 *    ⚠ Most cheap relay boards are ACTIVE-LOW (LOW = coil energized).
 *      Set RELAY_ACTIVE_LOW to match your module.
 * ============================================================================
 */

#define RELAY_PIN        7
#define RELAY_ACTIVE_LOW true     // true  -> LOW turns relay ON (most boards)
                                  // false -> HIGH turns relay ON

const unsigned long INTERVAL_MS = 2000UL;   // 2 seconds ON and 2 seconds OFF

void setRelay(bool on) {
  digitalWrite(RELAY_PIN, (on ^ RELAY_ACTIVE_LOW) ? HIGH : LOW);
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  setRelay(false);               // make sure load starts OFF
}

void loop() {
  setRelay(true);                // RELAY ON  (2 s)
  delay(INTERVAL_MS);

  setRelay(false);               // RELAY OFF (2 s)
  delay(INTERVAL_MS);
}
