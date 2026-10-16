/*
 * ============================================================================
 *  SINGLE CHANNEL RELAY — 2 s ON / 2 s OFF  (8051: AT89C51/AT89S52, Keil C51)
 * ----------------------------------------------------------------------------
 *  MCU        : AT89C51 / AT89S52  (11.0592 MHz crystal)
 *  Module     : 1-channel 5 V relay board (via transistor driver!)
 *  Behaviour  : loop forever ->
 *                 relay ON  -> delay 2000 ms
 *                 relay OFF -> delay 2000 ms
 *
 *  Wiring
 *    P1.0 -> 1k -> NPN(2N2222) base; 10k base->GND; emitter->GND;
 *           collector -> relay coil -; coil + -> 5V; diode across coil.
 *    Or simply P1.0 -> IN of a relay module with built-in driver.
 * ============================================================================
 */

#include <reg52.h>

/* ---------------------------- relay control ------------------------------ */
sbit RELAY_PIN = P1 ^ 0;        /* P1.0 = relay driver input                */

#define RELAY_ACTIVE_LOW 1      /* 1 = LOW energizes relay (most modules)   */
                                /* 0 = HIGH energizes relay                 */

#define INTERVAL_MS      2000   /* 2 seconds ON and 2 seconds OFF           */

#define FOSC_MHZ         11.0592

/* -------------------- busy-wait delay (Timer 0, mode 1) ------------------ */
/* ~1 ms per call at 11.0592 MHz (65536 - 65536/... classic 1 ms reload).    */
static void timer0_delay_1ms(void)
{
    TH0 = (65536 - (unsigned int)(FOSC_MHZ * 1000.0)) / 256;
    TL0 = (65536 - (unsigned int)(FOSC_MHZ * 1000.0)) % 256;
    TR0 = 1;                    /* start timer                               */
    while (TF0 == 0) ;          /* wait for overflow                         */
    TR0 = 0;                    /* stop timer                                */
    TF0 = 0;                    /* clear flag                                */
}

static void delay_ms(unsigned int ms)
{
    unsigned int i;
    for (i = 0; i < ms; i++) {
        timer0_delay_1ms();
    }
}

static void set_relay(bit on)
{
#if RELAY_ACTIVE_LOW
    RELAY_PIN = on ? 0 : 1;
#else
    RELAY_PIN = on ? 1 : 0;
#endif
}

void main(void)
{
    TMOD = 0x01;                /* Timer 0, mode 1 (16-bit)                  */
    set_relay(0);               /* load starts OFF                           */

    while (1) {
        set_relay(1);           /* RELAY ON  (2 s)                           */
        delay_ms(INTERVAL_MS);

        set_relay(0);           /* RELAY OFF (2 s)                           */
        delay_ms(INTERVAL_MS);
    }
}
