#include "Setup.h"

#include "Config.h"
#include "adc.h"
#include "cpuclockinit.h"
#include "initPorts.h"
#include "MazeManipulation.h"
#include "softDelay.h"
#include "led.h"


void SetupCpu (void)
{

	PortsInit();
	cpuClockInit();
	AdcInit();


}

void SetupCode (void)
{
	unsigned char StartX = 0;
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





