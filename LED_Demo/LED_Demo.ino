/* Blinker Demo */


#include <avr/io.h>                               /* Define pins & ports */
#include <util/delay.h>                        /* built-in time function */

int main(void) {

 
  DDRD |= (( 1 << DDD2 ));                      /* Data Direction Register B:
                                                      writing a 1 to the bit
                                                          enables output. */
  
  while (1) {

    PORTD = (( 1 << PD2 ));               /* Turn on LED bit/pin in PORTB */
    _delay_ms(500);                                              /* wait */

    PORTD = (( 0 << PD2 ));              /* Turn off LED bit/pin in PORTB */
    _delay_ms(500);                                              /* wait */

  }                                                     /* End event loop */
  return 0;                                 /* This line is never reached */
}
