//Contains functions to setup MCU; a single place to put all the function calls required to initialise clocks, ports, interrupts, ADC, SPI, wireless module and timer
#include "Setup.h"
#include "Config.h"
#include "adc.h"
#include "cpuclockinit.h"
#include "initPorts.h"
#include "MazeManipulation.h"
#include "softDelay.h"
#include "spi.h"
#include "nRF24L01.h"
#include "Interrupt.h"
#include "TimerA.h"

void SetupCpu (void)
{
	cpuClockInit();
	PortsInit();
	InitInterrupt();
	AdcInit();
	spiInit();
	rfPwrDown();
	rfWriteReg(REG_STATUS,TX_DS);	//Ensure that all interrupts are cleared
	rfWriteReg(REG_STATUS,RX_DR);	// on wireless module
	rfWriteReg(REG_STATUS,MAX_RT);
	rfConfig();
	rfWriteReg(REG_RF_CH,1);
	rfFlushRx();
	TimerAInit();

}

void SetupCode (void)
{
	unsigned char StartX = 3;
	unsigned char StartY = 3;

	ClearMaze();			//Clear out maze and set outside walls
	SetMouseY(StartY);		//Start in bottom left
	SetMouseX(StartX);
	SetMouseHeading(NORTH);

}

void WaitForSwitch (void)
{
	while (!SWITCH) softDelay(1000);
	while (SWITCH) softDelay(1000);
	softDelay(1000);
}

unsigned char IfSwitch (void)
{
	if (SWITCH)
	{
		while (SWITCH) softDelay(1000);
		softDelay(1000);
		return 1;
	}
	return 0;
}



