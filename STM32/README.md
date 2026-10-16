# STM32 — Single Channel Relay (2 s ON / 2 s OFF)

Target: STM32F103C8T6 "Blue Pill" (works for other STM32 F1/F4 boards with pin changes).

## File

| File | Description |
|---|---|
| `relay_2s_on_off/relay_2s_on_off.ino` | Arduino-core (STM32duino) sketch — blocking version |

## Default pin

**PB12** (Arduino pin name `PB12` on STM32duino). Any free 5 V-tolerant GPIO works.

```
Relay IN  -> PB12
Relay VCC -> 5V (or 3.3V if your module is 3.3 V logic — most accept 3.3 V on IN)
Relay GND -> GND
```

> ⚠ Blue Pill 3.3 V pins are **not** 5 V tolerant on all pins — PB12 is 5 V tolerant,
> but powering the relay coil from the Blue Pill's 3.3 V regulator is not recommended.
> Power the relay module from 5 V and share GND.

## Settings

```cpp
#define RELAY_PIN        PB12
#define RELAY_ACTIVE_LOW true    // false if your module switches on HIGH
```

## Upload (Arduino IDE)

1. Install "STM32 MCU based boards" via Boards Manager (STMicroelectronics)
2. Tools → Board → STM32F1 Boards → Generic STM32F103C series
   - Upload method: "Serial" via USB-TTL on PA9/PA10, or "STLink"
3. Upload.

## Timing

- ON = 2000 ms, OFF = 2000 ms → period 4 s.
