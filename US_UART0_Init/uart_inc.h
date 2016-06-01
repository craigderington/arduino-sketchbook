/*
	Initialize the UART as Library
*/

#ifndef UARTInit
#define UARTInit

#define EVEN 0
#define ODD 1

#include <math.h>
#include <avr/io.h>

unsigned char ReceiveUART0(void)
{
	// wait to receive data in the buffer
	while (! (UCSR0A & (1 << RXC0)) );

	// return received data
	return UDR0;
}

void TransmitUART0(unsigned char data)
{
	// wait until the tx is ready
	while (! (UCSR0A & (1 << UDRE0)) );
	
	// transmit the buffer data
	UDR0 = data;
}

void InitializeUART0(int baud, char AsyncDoubleSpeed, char DataSizeInBits, char ParityEVENorODD, char StopBits)
{
	// calculate the initial UBBR value 
	uint16_t UBBRValue = lrint(( F_CPU / (16L * baud ) - 1));

	// set the U2X bit to 1 for double speed async
	if (AsyncDoubleSpeed == 1) UCSR0A = (1 << U2X0);

	// put the upper part of the baud rate here (bits 8 to 11)
	UBRR0H = (unsigned char) (UBBRValue >> 8);

	// put the remaining part of the baud rate here
	UBRR0L = (unsigned char) UBBRValue;

	// enable the rx/tx
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// set 2 stop bits
	if (StopBits == 2) UCSR0C = (1 << USBS0);

	// check for parity
	if (ParityEVENorODD == EVEN) UCSR0C |= (1 << UPM01);
	if (ParityEVENorODD == ODD) UCSR0C |= (3 << UPM00);

	// check the data size in bits
	if (DataSizeInBits == 6) UCSR0C |= (1 << UCSZ00);
	if (DataSizeInBits == 7) UCSR0C |= (2 << UCSZ00);
	if (DataSizeInBits == 8) UCSR0C |= (3 << UCSZ00);
	if (DataSizeInBits == 9) UCSR0C |= (7 << UCSZ00);

}

void InitializeUART1(int baud, char AsyncDoubleSpeed, char DataSizeInBits, char ParityEVENorODD, char StopBits)
{
	// calculate the initial UBBR1 value
	uint16_t UBBRValue = lrint(( F_CPU / (16L * baud ) - 1));

	// set the U2X bit to 1 for double speed async
	if (AsyncDoubleSpeed == 1) UCSR1A = (1 << U2X1); 

	// put the upper part of the baud rate here (bits 8 to 11)
	UBRR1H = (unsigned char) (UBBRValue >> 8);

	// put the remaining part of the baud rate here
	UBRR1L = (unsigned char) UBBRValue;

	// enable the rx/tx
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);

	// set 2 stop bits
	if (StopBits == 2) UCSR1C = (1 << USBS1);

	// check the parity
	if (ParityEVENorODD == EVEN) UCSR1C |= (1 << UPM11);
	if (ParityEVENorODD == ODD) UCSR1C |= (3 << UPM10);

	// check the data size in bits
	if (DataSizeInBits == 6) UCSR1C |= (1 << UCSZ10);
	if (DataSizeInBits == 7) UCSR1C |= (2 << UCSZ10);
	if (DataSizeInBits == 8) UCSR1C |= (3 << UCSZ10);
	if (DataSizeInBits == 9) UCSR1C |= (7 << UCSZ10);

}

#endif
