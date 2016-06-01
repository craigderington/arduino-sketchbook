/*
 * ATtiny841_uart.c
 *
 * Created: 24-09-2014 17:11:38
 *  Author: Nishant
 */ 

// AVR306: Using the AVR UART in C
// Routines for polled USART
// Last modified: 02-06-21
// Modified by: AR

#define F_CPU 1000000UL

/* Includes */
#include <avr/io.h>
#include <util/delay.h>

/* Prototypes */
void USART0_Init( unsigned int baudrate );
unsigned char USART0_Receive( void );
void USART0_Transmit( unsigned char data );

/* Main - a simple test program*/
int main( void )
{
	USART0_Init( 6 ); /* Set the baudrate to 9600 bps using a 1.0000MHz INTOSC/crystal CKDIV8 set */

	for(;;) 	    /* Forever */
	{
		USART0_Transmit(USART0_Receive()); /* Echo the received character */
		//_delay_ms(1000);
	}
}

/* Initialize UART */
void USART0_Init( unsigned int baudrate )
{
	/* Set the baud rate */
	UBRR0H = (unsigned char) (baudrate>>8);
	UBRR0L = (unsigned char) baudrate;
	
	/* Enable UART receiver and transmitter */
	UCSR0B = ( ( 1 << RXEN0 ) | ( 1 << TXEN0 ) );
	
	/* Set frame format: 8 data 2stop */
	UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);              //For devices with Extended IO
	//UCSR0C = (1<<URSEL)|(1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);   //For devices without Extended IO
}


/* Read and write functions */
unsigned char USART0_Receive( void )
{
	/* Wait for incomming data */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Return the data */
	return UDR0;
}

void USART0_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1<<UDRE0)) )
	;
	/* Start transmittion */
	UDR0 = data;
}
