/* init uart */

void USART0_Init( unsigned int baudrate )
{
	/* set baud rate */
	UBRR0H = (unsigned char) (baudrate>>8);
	UBRR0L = (unsigned char) baudrate;
	
	/* enable the rx/tx */
	UCSR0B = ( ( 1 << RXEN0 ) | ( 1 << TXEN0 ) );
	
	/* set frame format: 8 data 2stop */
	UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
	//UCSR0C = (1<<URSEL)|(1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
}


/* read and write functions */
unsigned char USART0_Receive( void )
{
	/* wait for incomming data */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* return the data */
	return UDR0;
}

void USART0_Transmit( unsigned char data )
{
	/* wait for empty transmit buffer */
	while ( !(UCSR0A & (1<<UDRE0)) )
	;
	/* start transmittion */
	UDR0 = data;
}