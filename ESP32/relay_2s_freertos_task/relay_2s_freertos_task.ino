/*
 * ============================================================================
 *  SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (ESP32, FreeRTOS task version)
 * ----------------------------------------------------------------------------
 *  Board      : ESP32 DevKit / WROOM
 *  Module     : 1-channel 5 V relay board
 *  Behaviour  : A dedicated FreeRTOS task toggles the relay every 2 s using
 *               vTaskDelay() — the main loop() remains completely free.
 *
 *  Wiring: Relay IN -> GPIO26, VCC -> 5V, GND -> GND
 * ============================================================================
 */

#define RELAY_PIN        26
#define RELAY_ACTIVE_LOW true

const TickType_t INTERVAL_TICKS = pdMS_TO_TICKS(2000);   // 2 seconds

bool relayState = false;

void setRelay(bool on) {
  relayState = on;
  digitalWrite(RELAY_PIN, (on ^ RELAY_ACTIVE_LOW) ? HIGH : LOW);
}

/*
 * Relay task: toggles the coil ON for 2 s, then OFF for 2 s, forever.
 * Created on core 1 with priority 1 (see setup()).
 */
void relayTask(void *parameter) {
  for (;;) {
    setRelay(true);
    Serial.println("RELAY ON");
    vTaskDelay(INTERVAL_TICKS);

    setRelay(false);
    Serial.println("RELAY OFF");
    vTaskDelay(INTERVAL_TICKS);
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  setRelay(false);
  Serial.begin(115200);

  // Start the relay control task:
  xTaskCreatePinnedToCore(
      relayTask,      // function
      "RelayTask",    // name
      4096,           // stack size (bytes)
      NULL,           // parameter
      1,              // priority
      NULL,           // task handle
      1               // core 1 (core 0 runs WiFi)
  );
}

void loop() {
  // Main loop is free for WiFi, sensors, web server, etc.
  vTaskDelay(pdMS_TO_TICKS(1000));
}
