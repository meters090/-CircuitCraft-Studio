#!/usr/bin/env python3
"""
=============================================================================
 SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (Raspberry Pi)
 ----------------------------------------------------------------------------
 Target : Raspberry Pi 1/2/3/4/5/Zero (Raspberry Pi OS, Python 3)
 Module : 1-channel 5 V relay board
 Behavior: loop forever ->
             relay ON  -> sleep 2 s
             relay OFF -> sleep 2 s

 Wiring
   Relay IN  -> BCM GPIO 17 (physical pin 11)   [change RELAY_PIN below]
   Relay VCC -> 5V   (physical pin 2/4)
   Relay GND -> GND  (physical pin 6)
   Most cheap relay boards are ACTIVE-LOW (LOW = coil energized).
   Set RELAY_ACTIVE_LOW to match your module.

 Run:
   sudo apt install -y python3-rpi.gpio
   python3 relay_control.py
 Stop with Ctrl+C (GPIO is cleaned up on exit).
=============================================================================
"""

import time
import RPi.GPIO as GPIO

# ----------------------------- configuration -------------------------------
RELAY_PIN = 17                 # BCM pin connected to relay IN
RELAY_ACTIVE_LOW = True        # True  -> LOW turns relay ON (most boards)
                               # False -> HIGH turns relay ON
INTERVAL = 2.0                 # seconds ON and seconds OFF


def set_relay(on: bool) -> None:
    """Energize the relay coil according to the module's active level."""
    active_level = GPIO.LOW if RELAY_ACTIVE_LOW else GPIO.HIGH
    inactive_level = GPIO.HIGH if RELAY_ACTIVE_LOW else GPIO.LOW
    GPIO.output(RELAY_PIN, active_level if on else inactive_level)


def main() -> None:
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(RELAY_PIN, GPIO.OUT, initial=GPIO.HIGH if RELAY_ACTIVE_LOW else GPIO.LOW)

    print(f"Relay test started: 2 s ON / 2 s OFF on BCM GPIO {RELAY_PIN}")
    print("Press Ctrl+C to stop.")

    try:
        while True:
            set_relay(True)                # RELAY ON  (2 s)
            print(time.strftime("%H:%M:%S") + "  RELAY ON")
            time.sleep(INTERVAL)

            set_relay(False)               # RELAY OFF (2 s)
            print(time.strftime("%H:%M:%S") + "  RELAY OFF")
            time.sleep(INTERVAL)
    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        set_relay(False)                   # leave the load OFF
        GPIO.cleanup(RELAY_PIN)


if __name__ == "__main__":
    main()
