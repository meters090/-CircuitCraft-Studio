# PIC — Single Channel Relay (2 s ON / 2 s OFF)

Target: **PIC16F877A** (adaptable to PIC16F877A / PIC18F4550 etc. by changing config bits).

## File

| File | Description |
|---|---|
| `relay_2s_main.c` | XC8 C source — blocking 2 s ON / 2 s OFF loop |
| `relay_2s.X/` project notes below | MPLAB X project setup |

## Default pin

**RB0** (PORTB bit 0, physical pin 33 on PIC16F877A).

```
Relay IN  -> RB0 (through NPN transistor if module has no input driver)
Relay VCC -> 5V
Relay GND -> GND (common)
```

> ⚠ PIC pins source/sink only ~25 mA — **never drive a relay coil directly**.
> Always use a transistor/MOSFET driver or a module with a built-in one.

## Settings

```c
#define RELAY_PIN        PORTBbits.RB0
#define RELAY_ACTIVE_LOW 1    // 0 if your module switches on HIGH
```

## Build (MPLAB X + XC8)

1. File → New Project → Microchip → Embedded → MPLAB X IDE → XC8
2. Device: `PIC16F877A`
3. Add `relay_2s_main.c` to Source Files
4. Make & Program (PICkit 2/3/4 on ICSP: MCLR, PGD, PGC, VDD, VSS)

## Timing

- `_delay_ms(2000)` inside the loop → 2 s ON, 2 s OFF, 4 s period.
- Uses the internal 4 MHz oscillator (FOSC = HS/XT per config bits).
