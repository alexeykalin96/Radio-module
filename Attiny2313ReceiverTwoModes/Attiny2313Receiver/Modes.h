#ifndef Modes_H
#define Modes_H

#define JUMPER 0
#define MODE_NO 0
#define MODE_NO_JUMPER 1
#define MODE_YES_JUMPER 3
#define RELAY_ONE 3
#define RELAY_TWO 4

class Modes
{
	private:
		bool jumperState;
	
	public:
		void initPorts(void);
		bool getJumperState(void);
};

#endif