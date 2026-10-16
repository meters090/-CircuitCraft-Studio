# ARDUINO — Single Channel Relay (2 s ON / 2 s OFF)

Target: Arduino Uno / Nano / Mega (and any board supported by the Arduino IDE).

## Files

| File | Description |
|---|---|
| `relay_2s_on_off/relay_2s_on_off.ino` | Blocking version using `delay()` — simplest |
| `relay_2s_nonblocking/relay_2s_nonblocking.ino` | `millis()` version — loop stays free for other work |

## Default pin

| Board | Relay IN pin |
|---|---|
| Uno / Nano | `D7` (Arduino pin 7) |
| Mega 2560 | pin `7` |

Change `RELAY_PIN` at the top of the sketch for other wiring.

## Settings

```cpp
#define RELAY_PIN       7
#define RELAY_ACTIVE_LOW true   // false if your module switches on HIGH
```

## Upload

1. IDE → Tools → Board → Arduino AVR Boards → Arduino Uno
2. IDE → Sketch → Upload (Ctrl+U)

## Timing

- ON  = 2000 ms, OFF = 2000 ms → full period 4 s, 50 % duty cycle.
