# ESP32 — Single Channel Relay (2 s ON / 2 s OFF)

Target: ESP32 DevKit / WROOM / WROVER boards (Arduino core for ESP32).

## Files

| File | Description |
|---|---|
| `relay_2s_on_off/relay_2s_on_off.ino` | Blocking version (`delay`) |
| `relay_2s_freertos_task/relay_2s_freertos_task.ino` | Relay toggled in its own FreeRTOS task |

## Safe output pins (avoid these!)

Use **GPIO 26** (default here). Safe general-purpose outputs:
`2, 4, 5, 12–19, 21–23, 25–27, 32, 33`.

Avoid: `0, 1, 3` (boot/UART), `6–11` (flash), `34–39` (**input only**).

## Settings

```cpp
#define RELAY_PIN        26
#define RELAY_ACTIVE_LOW true   // false if your module switches on HIGH
```

## Upload (Arduino IDE)

1. Install "esp32" by Espressif Systems via Boards Manager
   (URL: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`)
2. Tools → Board → ESP32 Dev Module
3. Select COM port → Upload.

## Timing

- ON = 2000 ms, OFF = 2000 ms → period 4 s.
- FreeRTOS version runs the toggle in a 1-core task with `vTaskDelay`,
  leaving the main loop free.
