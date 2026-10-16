# RASPBERRY PI — Single Channel Relay (2 s ON / 2 s OFF)

Target: Raspberry Pi 1 / 2 / 3 / 4 / 5 / Zero (Raspberry Pi OS, Python 3).

## File

| File | Description |
|---|---|
| `relay_control.py` | Main program — toggles the relay every 2 seconds |

## Default pin

Uses **BCM GPIO 17** (physical pin 11). Change `RELAY_PIN` in the script.

```
Relay IN  -> BCM 17 (physical 11)
Relay VCC -> 5V   (physical 2 or 4)
Relay GND -> GND  (physical 6)
```

## Run

```bash
sudo apt update && sudo apt install -y python3-rpi.gpio
python3 relay_control.py
```

Stop with `Ctrl+C` — the script cleans up the GPIO on exit.

> **Note:** On Raspberry Pi 5, `RPi.GPIO` may not be supported — use the
> `rpi-lgpio` drop-in package (`sudo apt install python3-rpi-lgpio`) instead.

## Settings

```python
RELAY_PIN = 17              # BCM numbering
RELAY_ACTIVE_LOW = True     # False if your relay board switches on HIGH
INTERVAL = 2.0              # seconds ON and seconds OFF
```

## Timing

- ON = 2 s, OFF = 2 s → full period 4 s.
