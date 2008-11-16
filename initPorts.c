/*
Initialise all ports on microcontroller board.
*/

#include <io.h>
#include "initPorts.h"
#include "led.h"
#include "Motor2.h"

void PortsInit(void)
{


	P1SEL = 0x00;	// All digital signal i/o
	P1DIR = 0xFF;	//All output

	P2SEL = 0x00;	//All digital signal i/o
	P2DIR = 0xFF;	//All output

	P3SEL = 0x1F;	// [3.5] & [3.6] & [3.7] digital i/o [0001|1111]	//3.5 is switch
	P3DIR = 0x80;	// [3.7] output, rest input	[1000|0000]

	P4SEL = 0x00;	//All digital signal i/o
	P4DIR = 0xFF;	//All output

	P5SEL = 0x00;	//All digital signal i/o			// Port 5 is all used for motors
	P5DIR = 0xFF;	//All output

	P6SEL = 0xFF;	//ALL Function [ADC]
	P6DIR = 0x00;	//ALL Input


	LED1OFF;
	LED2OFF;
	LED3OFF;
	LED4OFF;
	LED5OFF;
	LED6OFF;
	LED7OFF;
	LED8OFF;

	LED9OFF;
	LED10OFF;
	LED11OFF;
	LED12OFF;
	LED13OFF;
	LED14OFF;
	LED15OFF;
	LED16OFF;


	M1P1OFF;
	M1P2OFF;
	M1P3OFF;
	M1P4OFF;

	M2P1OFF;
	M2P2OFF;
	M2P3OFF;
	M2P4OFF;

}




