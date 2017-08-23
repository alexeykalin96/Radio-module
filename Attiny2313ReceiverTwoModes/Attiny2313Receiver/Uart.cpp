#include "Uart.h"
#include <avr/io.h>

volatile char Uart::address[3] = "9Y";
volatile char Uart::rxBuff[BUFF_LENGTH];
volatile uint8_t Uart::counterRxBuff = 0;
volatile char Uart::currentByte = 0;
volatile uint32_t Uart::timer = 0;

void Uart::InitUart(uint16_t speed)
{
	// setting the baud rate
	uint16_t baudrate = F_CPU/16/speed-1;
	UBRRH = baudrate>>8;
	UBRRL = baudrate;
	UCSRC = (0 << UPM1)|(0 << UPM0)|(0 << USBS)|(1 << UCSZ1)|(1 << UCSZ0); //Set frame: 8data, 1stop
}

void Uart::getchUartEn(void)
{
	UCSRB = (1 << RXCIE)|(1 << RXEN);
}


void Uart::readByte(void)
{
	currentByte = UDR; //Reading Uart
	
	//Begin message
	if(currentByte == '<')
	{
		counterRxBuff = 0;
		for(uint8_t i = 1; i < BUFF_LENGTH; i++)
		{
			rxBuff[i] = 0;
		}
		timer = 0;

	}
	
	//Buffer is filled
	if(counterRxBuff < BUFF_LENGTH)
	{
		rxBuff[counterRxBuff] = currentByte;
		counterRxBuff++;
	}
	
	//Clear buffer when it's overflowed
	else
	{
		for(uint8_t i = 0; i < BUFF_LENGTH; i++)
		{
			rxBuff[i] = 0;
		}
		counterRxBuff = 0;
	}
}

uint8_t Uart::readRxCommand(void)
{	
	if((rxBuff[0] == '<') && (rxBuff[5] == '>'))
	{
		if((rxBuff[1] == address[0]) && (rxBuff[2] == address[1]) && (rxBuff[3] == 'A') && (rxBuff[4] == '1'))
		{
			uartCommand = BUT_ONE;
		}
		
		else if((rxBuff[1] == address[0]) && (rxBuff[2] == address[1]) && (rxBuff[3] == 'B') && (rxBuff[4] == '2'))
		{
			uartCommand = BUT_TWO;
		}
	}		
	
	return uartCommand;	
}

void Uart::cleaRxBuff(void)
{
	for(uint8_t i = 0; i < BUFF_LENGTH; i++)
	{
		rxBuff[i] = 0;
	}
	uartCommand = BUT_NO;
}

void Uart::initTimer0(void)
{
	TCCR0B = (1 <<  CS02)|(0 <<  CS01)|(1 <<  CS00);
	TIMSK |= (1 << TOIE0);
}

void Uart::Timer0(void)
{
	timer++;
}

uint16_t Uart::getTimer0(void)
{
	return timer;
}
