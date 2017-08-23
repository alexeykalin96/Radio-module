/*
 * SleepMode.cpp
 *
 * Created: 27.07.2017 14:38:16
 *  Author: user
 */ 

#define F_CPU 9600000UL

#define BUTTON_OPEN 3
#define BUTTON_CLOSE 4
#define LED_OUT 0

#include <avr/io.h>
#include <avr/sleep.h> // здесь описаны режимы сна
#include <avr/interrupt.h> // работа с прерываниями
#include <util/delay.h>
#include "ProgramUart.h"
#include "ProgramUart.cpp"

uint8_t timer = 0;

void initPCINT0(void)
{
	PCMSK |= (1 <<  PCINT3)|(1 <<  PCINT4);
	GIMSK |= (1 << PCIE);
}

void initTIMER0(void)
{
	TCCR0B = (1 << CS02)|(0 << CS01)|(1 << CS00);
	TIMSK0 |= (1 <<  TOIE0);
}

int main() 
{
	_delay_ms(100);
	
	DDRB |= (1 << LED_OUT);
	PORTB &= ~(1 << LED_OUT);
	
	initTIMER0();
	initPCINT0();
	
	ProgramUart progamUart;
	progamUart.UART_init();
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); // если спать - то на полную
	
	sei();
	
	while(1) {
		if(timer <= 20)
		{
			if(((PINB & (1 << BUTTON_OPEN)) == (0 << BUTTON_OPEN)) && ((PINB & (1 << BUTTON_CLOSE)) == (1 << BUTTON_CLOSE)))
			{
				progamUart.UART_send("<9YA1>");
				timer = 0;
				PORTB |= (1 << LED_OUT);
				
			}
			else if(((PINB & (1 << BUTTON_OPEN)) == (1 << BUTTON_OPEN)) && ((PINB & (1 << BUTTON_CLOSE)) == (0 << BUTTON_CLOSE)))
			{
				progamUart.UART_send("<9YB2>");
				timer = 0;
				PORTB |= (1 << LED_OUT);
			}
			else
			{
				PORTB &= ~(1 << LED_OUT);
			}
		}
		else if(timer > 20)
		{
			DDRB |= (1 << 1);
			PORTB &= ~(1 << 1);
			sleep_enable(); // разрешаем сон
			sleep_cpu(); // спать!
		}
	}
}

ISR(PCINT0_vect)
{
	sleep_disable();
	timer = 0;
}

ISR(TIM0_OVF_vect)
{
	timer++;
}