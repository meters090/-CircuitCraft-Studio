/*
 * ============================================================================
 *  SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (AVR bare metal, ATmega328P)
 * ----------------------------------------------------------------------------
 *  MCU        : ATmega328P @ 16 MHz (Arduino Uno/Nano chip, no Arduino core)
 *  Module     : 1-channel 5 V relay board
 *  Behaviour  : loop forever ->
 *                 relay ON  -> delay 2000 ms
 *                 relay OFF -> delay 2000 ms
 *
 *  Wiring: Relay IN -> PB0 (Arduino D8), VCC -> 5V, GND -> GND
 *          ⚠ Most relay boards are ACTIVE-LOW — set RELAY_ACTIVE_LOW to match.
 * ============================================================================
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#ifndef F_CPU
#define F_CPU 16000000UL        /* 16 MHz Arduino clock                      */
#endif

/* ---------------------------- relay control ------------------------------ */
#define RELAY_PORT       PORTB
#define RELAY_DDR        DDRB
#define RELAY_BIT        0                       /* PB0 (Arduino D8)        */
#define RELAY_ACTIVE_LOW 1   /* 1 = LOW energizes relay (most boards)       */
                             /* 0 = HIGH energizes relay                    */

#define INTERVAL_MS      2000.0   /* 2 seconds ON and 2 seconds OFF         */

static void set_relay(bool on)
{
    bool level = RELAY_ACTIVE_LOW ? !on : on;
    if (level) {
        RELAY_PORT |=  (1 << RELAY_BIT);
    } else {
        RELAY_PORT &= ~(1 << RELAY_BIT);
    }
}

int main(void)
{
    RELAY_DDR  |=  (1 << RELAY_BIT);   /* PB0 as output                     */
    RELAY_PORT &= ~(1 << RELAY_BIT);   /* start LOW                         */
    set_relay(false);                  /* load starts OFF                   */

    while (1) {
        set_relay(true);               /* RELAY ON  (2 s)                   */
        _delay_ms(INTERVAL_MS);

        set_relay(false);              /* RELAY OFF (2 s)                   */
        _delay_ms(INTERVAL_MS);
    }

    return 0;   /* never reached                                             */
}
