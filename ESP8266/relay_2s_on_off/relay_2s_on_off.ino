/*
 * ============================================================================
 *  SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (ESP8266, blocking version)
 * ----------------------------------------------------------------------------
 *  Board      : NodeMCU v2 / Wemos D1 mini / any ESP8266 board
 *  Module     : 1-channel 5 V relay board
 *  Behaviour  : loop forever ->
 *                 relay ON  -> wait 2000 ms
 *                 relay OFF -> wait 2000 ms
 *
 *  Wiring
 *    Relay IN  -> D1 (GPIO5)  — change RELAY_PIN below if needed
 *    Relay VCC -> 5V (VIN) or external 5 V supply
 *    Relay GND -> GND (common with MCU)
 *    ⚠ Most cheap relay boards are ACTIVE-LOW (LOW = coil energized).
 *      Set RELAY_ACTIVE_LOW to match your module.
 *    ⚠ Use only safe output pins: D1(5), D2(4), D5(14), D6(12), D7(13).
 * ============================================================================
 */

#define RELAY_PIN        5      // D1 on NodeMCU / D1 mini (GPIO5)
#define RELAY_ACTIVE_LOW true   // true -> LOW turns relay ON (most boards)

const unsigned long INTERVAL_MS = 2000UL;   // 2 seconds ON and 2 seconds OFF

void setRelay(bool on) {
  digitalWrite(RELAY_PIN, (on ^ RELAY_ACTIVE_LOW) ? HIGH : LOW);
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  setRelay(false);              // load starts OFF
}

void loop() {
  setRelay(true);               // RELAY ON  (2 s)
  delay(INTERVAL_MS);

  setRelay(false);              // RELAY OFF (2 s)
  delay(INTERVAL_MS);
}
