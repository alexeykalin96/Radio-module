#ifndef Uart_H
#define Uart_H

#define BUFF_LENGTH 6

#define BUT_NO 0
#define BUT_ONE 1
#define BUT_TWO 2

class Uart
{
	private:
		static volatile char address[3];
		static volatile char rxBuff[BUFF_LENGTH];
		static volatile uint8_t counterRxBuff;
		static volatile char currentByte;
		uint8_t volatile uartCommand;
		static volatile uint32_t timer;
	
	public:
		void InitUart(uint16_t speed);
		void getchUartEn(void);
		static void readByte(void);
		uint8_t readRxCommand(void);
		void cleaRxBuff(void);
		void initTimer0(void);
		static void Timer0(void);
		static uint16_t getTimer0(void);
};

#endif