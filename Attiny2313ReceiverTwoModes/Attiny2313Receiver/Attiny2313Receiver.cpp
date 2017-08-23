/*
 * Attiny2313Receiver.cpp
 *
 * Created: 11.08.2017 10:21:39
 *  Author: user
 */ 


#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Modes.h"
#include "Modes.cpp"
#include "Uart.h"
#include "Uart.cpp"

int main(void)
{
	_delay_ms(500);
	
	Modes modes;
	modes.initPorts();
	uint8_t currentMode = MODE_NO;
		
	Uart uart;
	uart.InitUart(2000);
	uart.getchUartEn();
	uint8_t currentCommand = BUT_NO;
	
	switch(modes.getJumperState())
	{
		case false:
			currentMode = MODE_NO_JUMPER;
			uart.initTimer0();
		break;
		
		case true:
			currentMode = MODE_YES_JUMPER;
		break;
		
		default:
			currentMode = MODE_NO;		
	}
	
	sei();
	
	while(1)
	{
		switch(currentMode)
		{
			//button1 is pressed --- relay1 is on and relay2 is off
			//button2 is pressed --- relay2 is on and relay1 is off
			case MODE_NO_JUMPER:
				if(currentCommand != uart.readRxCommand())
				{
					currentCommand = uart.readRxCommand();
					switch(currentCommand)
					{
						case BUT_NO:
						PORTB &= ~((1 << RELAY_ONE)|(1 << RELAY_TWO));
						break;
						
						case BUT_ONE:
						PORTB &= ~(1 << RELAY_TWO);
						PORTB |= (1 << RELAY_ONE);
						break;
						
						case BUT_TWO:
						PORTB &= ~(1 << RELAY_ONE);
						PORTB |= (1 << RELAY_TWO);
						break;
					}
				}
				
				if(uart.getTimer0() > 18)
				{
					PORTB &= ~((1 << RELAY_ONE)|(1 << RELAY_TWO));
					uart.cleaRxBuff();
				}
			break;	
			
			
			//button 1 is pressed --- relay1 and relay2 is on
			//button 2 is pressed --- relay1 and relay2 is off
			case MODE_YES_JUMPER:
				if(currentCommand != uart.readRxCommand())
				{
					currentCommand = uart.readRxCommand();
					switch(currentCommand)
					{	
						case BUT_ONE:
						//PORTB |= (1 << RELAY_TWO);
						PORTB |= (1 << RELAY_ONE);
						break;
						
						case BUT_TWO:
						PORTB &= ~(1 << RELAY_ONE);
						//PORTB &= ~(1 << RELAY_TWO);
						break;
					}
				}
			break;	
			
			default:
			
			break;
			
		}
		
	}
}

ISR(USART_RX_vect, ISR_BLOCK)
{
	Uart::readByte();
}

ISR(TIMER0_OVF_vect)
{
	Uart::Timer0();
}