# AVR (bare metal) — Single Channel Relay (2 s ON / 2 s OFF)

Target: **ATmega328P** (Arduino Uno/Nano chip) programmed without the Arduino
framework — pure avr-gcc, for learning register-level AVR.

## File

| File | Description |
|---|---|
| `relay_2s_main.c` | avr-gcc C source — blocking 2 s ON / 2 s OFF loop |
| `Makefile` | `make`, `make flash`, `make clean` |

## Default pin

**PB0** (Arduino digital pin **8**), using the datasheet-style `PORTB`/`DDRB`.

```
Relay IN  -> PB0 (pin 14 on DIP-28 / Arduino D8)
Relay VCC -> 5V
Relay GND -> GND
```

## Settings

```c
#define RELAY_BIT        0      /* PB0 */
#define RELAY_ACTIVE_LOW 1      /* 0 if your module switches on HIGH */
```

## Build

```bash
# Debian/Ubuntu: sudo apt install gcc-avr avr-libc avrdude
make            # builds relay_2s_main.hex
make flash      # uploads via avrdude -c arduino -P COMx -b 115200
```

Windows: use `avr-gcc` from the Microchip toolchain and
`avrdude -c arduino -P COM5 -b 115200 -p m328p -U flash:w:relay_2s_main.hex:i`

## Timing

- `my_delay_ms(2000)` — busy-loop `_delay_ms()` from `<util/delay.h>`
- ON = 2 s, OFF = 2 s → period 4 s, 50 % duty cycle.
