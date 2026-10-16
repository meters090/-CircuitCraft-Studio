# SINGLE CHANNEL RELAY — Multi-Microcontroller Relay Control

A single-channel **5V relay module** that toggles:

```
RELAY = ON  → 2 seconds
RELAY = OFF → 2 seconds
(repeats forever)
```

This repository contains **ready-to-flash code for many microcontrollers**, each in its
own folder so you can copy only the one you need.

## Folder Map

| Folder | Target | Language / Toolchain |
|---|---|---|
| [`ARDUINO/`](ARDUINO/) | Arduino Uno / Nano / Mega (ATmega328P/2560) | Arduino C++ (`.ino`) |
| [`RASPBERRY_PI/`](RASPBERRY_PI/) | Raspberry Pi 1/2/3/4/5, Zero | Python 3 (`RPi.GPIO`) |
| [`ESP8266/`](ESP8266/) | NodeMCU / Wemos D1 mini | Arduino C++ (`.ino`) |
| [`ESP32/`](ESP32/) | ESP32 DevKit / WROOM | Arduino C++ (`.ino`, FreeRTOS task) |
| [`STM32/`](STM32/) | STM32F103 "Blue Pill" | STM32duino (`.ino`) |
| [`PIC/`](PIC/) | PIC16F877A | C for XC8 |
| [`8051/`](8051/) | AT89C51 / AT89S52 | C for Keil µVision |
| [`AVR/`](AVR/) | ATmega328P (bare metal) | C for avr-gcc |

## How the relay timing works

Every project uses the same rule:

```
loop:
    relay = ON
    wait 2000 ms
    relay = OFF
    wait 2000 ms
```

Period = **4 seconds** (50% duty cycle), `ON time = OFF time = 2 s`.

## Wiring (common to all boards)

```
MCU GPIO ────[ 1kΩ ]────┐
                         ├─ NPN transistor (e.g. 2N2222 / S8050) base
                     [10kΩ] to GND

Relay module (most 5V 1-channel modules are ACTIVE-LOW):
  VCC  → 5V
  GND  → GND
  IN   → MCU GPIO (through the driver stage above, or direct if module has one)
  COM  → mains / load common
  NO   → load (relay is OPEN = OFF when unpowered)
```

> ⚠️ **SAFETY:** When switching mains voltage, keep wires insulated, fuse the live
> line, and never touch the circuit while powered. Use the relay's **NO** (Normally
> Open) contact so the load is OFF at reset.

### Active-LOW vs Active-HIGH

Many cheap 1-channel relay boards are **active-LOW** (IN = LOW energizes the coil).
All code here exposes a single flag:

```cpp
#define RELAY_ACTIVE_LOW true   // set false for active-HIGH modules
```

so one line adapts the sketch to your module.

## Timing options included

- **Blocking (`delay`)** — simplest, best for beginners.
- **Non-blocking (`millis()`)** — keeps the MCU responsive (Arduino, ESP folders).
- **RTOS task (ESP32)** — relay toggles in its own FreeRTOS task.

## Quick start

1. Open the folder for your board.
2. Read its `README.md` (flashing instructions + pin tables).
3. Set `RELAY_PIN` and `RELAY_ACTIVE_LOW` to match your wiring.
4. Build/flash, power the relay module, and listen for the 4-second click rhythm:
   `click … click …` every 2 seconds.
