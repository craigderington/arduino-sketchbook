/* 	

  ATTiny841 programming for Hall Effect Sensor on new ATTiny841 chipset
  Uses US_UART from the standard C library for serial communications
   
*/

// include standard libraries

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <power.h>

#ifndef F_CPU
#define F_CPU 8000000UL						    // set the CPU clock
#endif

#define BAUD 1200								// define baud
#define BAUDRATE ((F_CPU)/(BAUD*8UL)-1)		    // set baudrate value for UBRR

// declare vars
unsigned long lastlooptime = 0;
int pwmpin = 9;
int analogpin = 1;

// define pinouts
#define sensor1_pa3 ADC3
#define sensor_pa2 ADC2
#define uart_out_pa1 ADC1

// define timer function
unsigned long millis()
{
	unsigned long m;
	uint8_t oldSREG = SREG;

	cli();
	m = timer0_millis;
	SREG = oldSREG;

	return m;
}

// function to initialize universal asynchronous receive/transmit
void uart_init (void)
{
	UBRRH=(BAUDRATE>>8);
	UBRRL=BAUDRATE;								// set baud rate
	UCSRB|=(1<<TXEN)|(1<<RXEN); 				// enable receiver and transmitter
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);	// 8bit data format
}

// function to send data
void uart_transmit (unsigned char data)
{
	while (!( UCSRA & (1<<UDRE))); 			   // wait while register is free
	UDR = data; 							   // load data in the register
}

// function to receive data
unsigned char uart_receive (void)
{ 
	while(!(UCSRA) & (1<<RXC)); 			   // wait while data is being received
	return UDR; 							   // return 8-bit data
}

// main function: entry point of program
int main (void)
{
	
	// initialize UART 
	// Serial.begin(1200) in arduino sketch
	uart_init(); 			
								
  	while(1)
  	{
		
  		// if the last loop time <> 0 and is less than 3000 milliseconds, begin...
		// if(lastlooptime != 0 && millis() - lastlooptime < 3000 )
			// return;
		
			// short delay allowing system to start up
			_delay_ms(150);

			// set analog pin to full power
			// analogWrite(pwmpin, 255);

			// wait again for voltage to settle
			// _delay_ms(150);

			// create a 5 element array to hold the sensor readings
			int readings [5];

			// declare an interator
			int i;

			// loop the sensor readings by reading the pin value
			for(i = 0; i < 5; i++) {
				readings[i] = sensor_pa2(analogpin);
			}

			// calculate an average for the 5 sensor readings
			int sensorvalue = (readings[0] + readings[1] + readings[2] + readings[3] + readings[4]) / 5;

			// convert the average sensor reading to a voltage
			float voltage = sensorvalue * (5.0 / 10.23);

			// kill power to A0
			// analogWrite(pwmpin, 0);

			// define message to be transmitted and format
			char voltread = [10];
			sprintf (voltread, "V;RB0%03i;",(int)voltage);

			// generate a checksum for the message to be transmitted
			signed char checksum = 0;
		    
		    for(int i = 0; i < 9; i++) checksum ^= voltread[i];
		    
		    //define transmission string to be sent to radio and add checksum to message then transmit
		 	char transmission[13];
		 	sprintf (transmission, "%s%x;", voltread, checksum);
		  	
		  	// send serial transmission to USUART;
		  	uart_transmit(transmission);
		  
		  	// wait 3 seconds a loop... this should not be reached in normal processing as power is only applied for 2.5 seconds
		  	// lastlooptime = millis();

		  	// put the chip to sleep
		  	power_all_disable();

  	}
  	
  	return 0;
}
