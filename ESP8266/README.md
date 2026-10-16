# ESP8266 — Single Channel Relay (2 s ON / 2 s OFF)

Target: NodeMCU v2 (ESP-12E), Wemos D1 mini, and other ESP8266 boards.

## File

| File | Description |
|---|---|
| `relay_2s_on_off/relay_2s_on_off.ino` | Blocking version (`delay`) |
| `relay_2s_nonblocking/relay_2s_nonblocking.ino` | `millis()` version — WiFi stack stays responsive |

## Safe GPIO pins on ESP8266

| Board label | GPIO | Safe as output? |
|---|---|---|
| D1 | GPIO5 | ✅ recommended (default in this code) |
| D2 | GPIO4 | ✅ recommended |
| D5/D6/D7 | 14/12/13 | ✅ |
| D0 | GPIO16 | ✅ |
| D8 | GPIO15 | ⚠ boot strap — must be LOW at boot |
| D3/D4 | 0/2 | ⚠ boot strap — must be HIGH at boot |
| — | GPIO1/3 | ❌ UART0 (TX/RX) — do not use |

**Never use GPIO16 for the relay if your module is active-LOW and powered from
3.3 V — relay boards pull ~70–80 mA; ESP8266 pins are limited to ~12 mA.
Use a transistor/MOSFET driver or a module with a built-in one.**

## Settings

```cpp
#define RELAY_PIN        5     // D1 on NodeMCU / D1 mini
#define RELAY_ACTIVE_LOW true  // false if your board switches on HIGH
```

## Upload (Arduino IDE)

1. Install ESP8266 core: File → Preferences → Additional Board Manager URLs:
   `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
2. Tools → Board → ESP8266 Boards → "NodeMCU 1.0 (ESP-12E Module)"
   (or "LOLIN(WEMOS) D1 R2 & mini")
3. Select the correct COM port → Sketch → Upload.

## Timing

- ON = 2000 ms, OFF = 2000 ms → period 4 s.
