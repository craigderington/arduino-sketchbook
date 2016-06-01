/* Blinker Demo */


#include <avr/io.h>                               /* Define pins & ports */
#include <util/delay.h>                        /* built-in time function */

int main(void) {

 
  DDRB |= ((1 << DDB5));                       /* Data Direction Register B:
                                                      writing a 1 to the bit
                                                          enables output. */
  
  while (1) {

    PORTB = (( 1 << PB5 ));               /* Turn on LED bit/pin in PORTB */
    _delay_ms(1000);                                              /* wait */

    PORTB = (( 0 << PB5 ));              /* Turn off LED bit/pin in PORTB */
    _delay_ms(1000);                                              /* wait */

  }                                                     /* End event loop */
  return 0;                                 /* This line is never reached */
}
