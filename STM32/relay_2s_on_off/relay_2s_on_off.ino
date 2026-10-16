/*
 * ============================================================================
 *  SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (STM32F103 "Blue Pill")
 * ----------------------------------------------------------------------------
 *  Board      : STM32F103C8T6 Blue Pill (STM32duino Arduino core)
 *  Module     : 1-channel 5 V relay board
 *  Behaviour  : loop forever ->
 *                 relay ON  -> wait 2000 ms
 *                 relay OFF -> wait 2000 ms
 *
 *  Wiring
 *    Relay IN  -> PB12 (change RELAY_PIN below if needed)
 *    Relay VCC -> 5V (external supply, share GND with MCU)
 *    Relay GND -> GND
 *    ⚠ Most cheap relay boards are ACTIVE-LOW (LOW = coil energized).
 * ============================================================================
 */

#define RELAY_PIN        PB12
#define RELAY_ACTIVE_LOW true    // true -> LOW turns relay ON (most boards)

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
