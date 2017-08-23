#ifndef ProgramUart_H
#define ProgramUart_H

#define TX_PIN 1

class ProgramUart
{
	private:
		void UART_bit(char bit);
		void UART_byte(char byte);
	
	public:
		void UART_init(void);
		void UART_send(char *str);
};

#endif