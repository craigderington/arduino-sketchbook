
// tiny841_uart_test.c
// ----------------
//  Created: 19.09.2014
//   Author: sschultewolter
// Hardware: ATtiny841 5V 8MHz(internal Oscillator)

#include <avr/io.h>
#include <avr/interrupt.h>

// UART0
#define UART0_BAUD 9600UL
#define UART0_UBRR_VAL ((F_CPU+UART0_BAUD*8)/(UART0_BAUD*16)-1)
#define UART0_BAUD_REAL (F_CPU/(16*(UART0_UBRR_VAL+1)))
#define UART0_BAUD_ERROR ((UART0_BAUD_REAL*1000)/UART0_BAUD)

#if ((UART0_BAUD_ERROR<990) || (UART0_BAUD_ERROR>1010))
#error UART0_BAUD_ERROR > 1%
#endif

void uart0_init(void)
{
	UBRR0 = UART0_UBRR_VAL;
	UCSR0B |= (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

int uart0_putc(uint8_t c)
{
	while(!(UCSR0A & (1<<UDRE0))) { }
	UDR0 = c;
	return 0;
}

void uart0_puts (char *s)
{
	while (*s)
	{
		uart0_putc(*s);
		s++;
	}
}

// UART1
#define UART1_BAUD 9600UL
#define UART1_UBRR_VAL ((F_CPU+UART1_BAUD*8)/(UART1_BAUD*16)-1)
#define UART1_BAUD_REAL (F_CPU/(16*(UART1_UBRR_VAL+1)))
#define UART1_BAUD_ERROR ((UART1_BAUD_REAL*1000)/UART1_BAUD)

#if ((UART1_BAUD_ERROR<990) || (UART1_BAUD_ERROR>1010))
#error UART0_BAUD_ERROR > 1%
#endif

void uart1_init(void)
{
	UBRR1 = UART1_UBRR_VAL;
	UCSR1B |= (1 << TXEN1);
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

int uart1_putc(uint8_t c)
{
	while(!(UCSR1A & (1<<UDRE1))) { }
	UDR1 = c;
	return 0;
}

void uart1_puts (char *s)
{
	while (*s)
	{
		uart1_putc(*s);
		s++;
	}
}


volatile uint32_t millis;

ISR(TIMER0_COMPA_vect)
{
	millis++;
}


int main(void)
{
	// UART
	uart0_init();
	uart1_init();
	
	// millis
	TCCR0A = (1 << WGM01);					// CTC Mode
	TCCR0B |= (1 << CS01) | (1 << CS00);	// Prescaler 64
	OCR0A = 124;							// (F_CPU/PRESCALER)/1000-1
	TIMSK0 |= (1 << OCIE0A);				// Compare Interrupt
	sei();
	
	while(1)
	{
		static uint16_t last_second;
		uint16_t second = millis / 1000;
		if(second != last_second)
		{
			last_second = second;
			
			char str[10];
			itoa(second, str, 10);
			
			uart0_puts("\n\r");
			uart0_puts("UART0 >> ");
			uart0_puts(str);

			uart1_puts("\n\r");
			uart1_puts("UART1 >> ");
			
			uart1_puts(str);
		}
	}
}