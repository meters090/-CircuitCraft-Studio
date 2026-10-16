/*
 * ============================================================================
 *  SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (ESP32, blocking version)
 * ----------------------------------------------------------------------------
 *  Board      : ESP32 DevKit / WROOM
 *  Module     : 1-channel 5 V relay board
 *  Behaviour  : loop forever ->
 *                 relay ON  -> wait 2000 ms
 *                 relay OFF -> wait 2000 ms
 *
 *  Wiring
 *    Relay IN  -> GPIO26 (change RELAY_PIN below if needed)
 *    Relay VCC -> 5V (VIN) or external 5 V supply
 *    Relay GND -> GND (common with MCU)
 *    ⚠ Most cheap relay boards are ACTIVE-LOW (LOW = coil energized).
 *    ⚠ Do NOT use GPIO 34–39 (input only) or 6–11 (flash).
 * ============================================================================
 */

#define RELAY_PIN        26
#define RELAY_ACTIVE_LOW true    // true -> LOW turns relay ON (most boards)

const unsigned long INTERVAL_MS = 2000UL;   // 2 seconds ON and 2 seconds OFF

void setRelay(bool on) {
  digitalWrite(RELAY_PIN, (on ^ RELAY_ACTIVE_LOW) ? HIGH : LOW);
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  setRelay(false);              // load starts OFF
  Serial.begin(115200);
}

void loop() {
  setRelay(true);               // RELAY ON  (2 s)
  Serial.println("RELAY ON");
  delay(INTERVAL_MS);

  setRelay(false);              // RELAY OFF (2 s)
  Serial.println("RELAY OFF");
  delay(INTERVAL_MS);
}
