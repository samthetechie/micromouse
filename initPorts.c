//Initialises all I/O ports on MCU
#include <io.h>
#include "initPorts.h"
#include "led.h"
#include "Motor2.h"
/*
Initialise all ports on microcontroller board.
*/

void PortsInit(void)
{

					//Port 1 is LedsLower
	P1SEL = 0x00;	// All digital signal i/o:	[0000|0000] = 0x00
	P1DIR = 0xFF;	//All output:				[1111|1111] = 0xFF

	P2SEL = 0x00;	//All digital signal i/o:	[0000|0000] = 0x00
	P2DIR = 0xFB;	//2.2 is input IRQ for wireless,2.3 is output [!CS] for nRF, 2.4 is output[CE] for wireless
						//rest are output: 		[1111|1011] = 0xFB

	P2IE  = 0x04;	//Enable interrupt for P2.2	[0000|0100] = 0x04
	P2IES = 0x04;	//Edge Select is H2L [\]	[0000|0100] = 0x04

	P3SEL = 0x0E;	//P3Bits [1,2,3] are SPI, rest are Di/o [0000|1110] = 0x0E, 	note:3.5 is switch
	P3DIR = 0xCA;	//[1,3,6,7] output1, [0,2,4,5] input0:	[1100|1010] = 0xCA

	P4SEL = 0x00;	//All digital signal i/o:	[0000|0000] = 0x00
	P4DIR = 0xFF;	//All output:				[1111|1111] = 0xFF

	P5SEL = 0x00;	//All digital signal i/o:	[0000|0000] = 0x00	// Port 5 is all used for motors
	P5DIR = 0xFF;	//All output:				[1111|1111] = 0xFF

	P6SEL = 0xFF;	//ALL Function [ADC]:		[1111|1111] = 0xFF
	P6DIR = 0x00;	//ALL Input:				[0000|0000] = 0x00


	LED1OFF;
	LED2OFF;
	LED3OFF;
	LED4OFF;
	LED5OFF;
	LED6OFF;
	LED7OFF;
	LED8OFF;

/*	LED9OFF;
	LED10OFF;
	LED11OFF;
	LED12OFF;
	LED13OFF;
	LED14OFF;
	LED15OFF;
	LED16OFF;
*/

	M1P1OFF;
	M1P2OFF;
	M1P3OFF;
	M1P4OFF;

	M2P1OFF;
	M2P2OFF;
	M2P3OFF;
	M2P4OFF;

}




