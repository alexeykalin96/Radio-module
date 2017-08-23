#include <avr/io.h>
#include <util/delay.h>

void ProgramUart::UART_init(void)
{
	DDRB |= (1 << TX_PIN);
	PORTB |= (1 << TX_PIN);
}

void ProgramUart::UART_bit(char bit)
{
	if (bit == 0x00)
	{
		PORTB &= ~(1 << TX_PIN);
	}
	_delay_us(500);
	PORTB |= (1 << TX_PIN);
}

void ProgramUart::UART_byte(char byte)
{
	UART_bit(0x00);//start bit
	for (uint8_t i = 0; i < 8; i++)
	{
		if ((byte >> i) & 0x01)
		{
			UART_bit(0x01);//data bit
		}
		else
		{
			UART_bit(0x00);//data bit
		}
	}
	UART_bit(0x01);//stop bit
}

void ProgramUart::UART_send(char *str)
{
	uint8_t i = 0;
	while (str[i])
	{
		UART_byte(str[i++]);
	}
}
