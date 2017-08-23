#include "Modes.h"

void Modes::initPorts(void)
{
	DDRB |= (1 << RELAY_ONE)|(1 << RELAY_TWO); //Relays as output
	PORTB &= ~((1 << RELAY_ONE)|(1 << RELAY_TWO)); //Relays off
	PORTB |= (1 << JUMPER); //Pull-up resistor to jumper
	DDRB &= ~(1 << JUMPER); //Jumper as input
}

bool Modes::getJumperState(void)
{
	if((PINB & (1 << JUMPER)) == (1 << JUMPER))
	{
		jumperState = false;
	}
	else if((PINB & (1 << JUMPER)) == (0 << JUMPER))
	{
		jumperState = true;
	}
	
	return jumperState;
}

