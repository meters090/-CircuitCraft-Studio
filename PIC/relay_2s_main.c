/*
 * ============================================================================
 *  SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (PIC16F877A, XC8 C)
 * ----------------------------------------------------------------------------
 *  MCU        : PIC16F877A  (change config bits / pin for other PICs)
 *  Module     : 1-channel 5 V relay board (via transistor driver!)
 *  Behaviour  : loop forever ->
 *                 relay ON  -> _delay_ms(2000)
 *                 relay OFF -> _delay_ms(2000)
 *
 *  Wiring
 *    RB0 (pin 33) -> 1k resistor -> NPN base (2N2222/S8050)
 *                    10k base->GND, emitter->GND, collector->relay coil -
 *                    coil + -> 5V,  flyback diode (1N4007) across coil
 *    Or use a relay module with a built-in driver: RB0 -> IN directly.
 *
 *    ⚠ PIC pins are NOT rated to drive a relay coil directly.
 * ============================================================================
 */

#include <xc.h>
#include <stdint.h>

/* ---------------------- device configuration bits ------------------------ */
#pragma config FOSC  = HS      /* HS oscillator (4 MHz crystal)              */
#pragma config WDTE  = OFF     /* Watchdog timer disabled                     */
#pragma config PWRTE = ON      /* Power-up timer enabled                      */
#pragma config BOREN = ON      /* Brown-out reset enabled                     */
#pragma config LVP   = OFF     /* RB3 is digital I/O (not low-voltage prog)  */
#pragma config CPD   = OFF     /* Data EEPROM code protection off            */
#pragma config WRT   = OFF     /* Flash write protection off                  */
#pragma config CP    = OFF     /* Code protection off                         */

#define _XTAL_FREQ 4000000UL   /* 4 MHz — required by __delay_ms()          */

/* ---------------------------- relay control ------------------------------ */
#define RELAY_PIN        LATBbits.LB0   /* RB0 = relay driver input          */
#define RELAY_TRIS       TRISBbits.TRISB0
#define RELAY_ACTIVE_LOW 1              /* 1 = LOW energizes relay           */
                                         /* 0 = HIGH energizes relay          */

#define INTERVAL_MS      2000UL         /* 2 seconds ON and 2 seconds OFF    */

static void set_relay(uint8_t on)
{
#if RELAY_ACTIVE_LOW
    RELAY_PIN = on ? 0 : 1;
#else
    RELAY_PIN = on ? 1 : 0;
#endif
}

void main(void)
{
    /* RB0 as output, all PORTB outputs low to start */
    RELAY_TRIS = 0;
    LATB = 0x00;
    set_relay(0);                       /* load starts OFF                   */

    while (1) {
        set_relay(1);                   /* RELAY ON  (2 s)                   */
        __delay_ms(INTERVAL_MS);

        set_relay(0);                   /* RELAY OFF (2 s)                   */
        __delay_ms(INTERVAL_MS);
    }
}
