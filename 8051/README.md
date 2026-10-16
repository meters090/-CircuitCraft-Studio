# 8051 — Single Channel Relay (2 s ON / 2 s OFF)

Target: **AT89C51 / AT89S52** (and compatible 8051 variants) — Keil µVision C51.

## File

| File | Description |
|---|---|
| `relay_2s_main.c` | Keil C source — blocking 2 s ON / 2 s OFF loop |

## Default pin

**P1.0** (PORT1 bit 0).

```
Relay IN  -> P1.0 (through NPN transistor driver!)
Relay VCC -> 5V
Relay GND -> GND (common)
```

> ⚠ 8051 pins can't drive a relay coil directly (~10–20 mA, coil needs 70–80 mA).
> Use a 2N2222/S8050 driver stage or a relay module with a built-in driver.

## Settings

```c
#define RELAY_PIN        P1_0    /* sbit for P1.0 */
#define RELAY_ACTIVE_LOW 1       /* 0 if your module switches on HIGH */
```

## Build (Keil µVision 5)

1. Project → New µVision Project → select `AT89C52`
2. Add `relay_2s_main.c` to Source Group 1
3. Project → Build (F7)
4. Flash the `.hex` with:
   - **AT89S52**: USB ISP programmer (e.g. USBasp / Arduino-as-ISP)
   - **AT89C51**: Universal programmer (e.g. TL866)

## Timing

- `delay_ms(2000)` from a 11.0592 MHz crystal timer loop → 2 s ON, 2 s OFF.
- The delay function uses Timer 0 in mode 1; tuned for 11.0592 MHz.
