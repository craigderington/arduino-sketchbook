/*
 * GccApplication1.c
 *
 * Created: 5/17/2016 9:10:46 AM
 * Author : TALABS-DEV
 */

#ifndef F_CPU
#define F_CPU 8000000UL
#endif 

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/power.h>

#define BAUD 1200
#define BAUDRATE ((F_CPU) / (BAUD*8UL)-1)

// define pins
#define sensor_1_pa3 ADC3D
#define sensor_pa2 ADC2D
#define uart_out_pa1 ADC1D

// function to initialize the uart
void uart_init (void)
{
	UBRR0H=(BAUDRATE>>8);
	UBRR0L=BAUDRATE;								// set the baud rate
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);					// enable the rx/tx
	UCSR0C|=(1<<UCSR0A)|(1<<UCSZ00)|(1<<UCSZ01);	// 8bit data format
}

void uart_transmit (unsigned char data)
{
	while (!( UCSR0A & (1<< UDRE0)));				// wait while the register is free
	data = UDRE0;									// load data in the register
	return;

}

unsigned char uart_receive (void)
{
	while (!(UCSR0A & (1<<RXEN0)));					// wait while the data is being received
	return UDRE0;									// return 8-bit data
}

int main(void)
{
    /* initialize the uart */
	uart_init();
    while (1) 
    {
		_delay_ms(150);
		
		// create a 5 element array to hold sensor reading values
		int readings [5];
		
		// declare an iterator
		int i;
		
		// loop the sensor readings and assign pin values
		for(i=0; i < 5; i++){
			readings[i] = ADC2D;
		}
		
		// calculate the average for the 5 sensor readings
		int sensorvalue = (readings[0] + readings[1] + readings[2] + readings[3] + readings[4]) / 5;
		
		// convert the average sensor reading to a voltage
		float voltage = sensorvalue * (5.0/10.23);
		
		// define and format message to be transmitted
		char voltread[10];
		sprintf(voltread, "V;RB0%03i", (int)voltage);
		
		// generate a checksum for the message to be transmitted
		signed char checksum = 0;
		
		for(int i = 0; i < 9; i++) checksum ^= voltread[i];
		
		// declare transmission string to be sent to radio and add checksum
		char transmission[13];
		char data;
		data = sprintf(transmission, "%s%x", voltread, checksum);
		
		// send transmission to uart
		uart_transmit(data);
		
		// put the chip to sleep
		power_all_disable();
    }
	
	return 0;
}

