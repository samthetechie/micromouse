#include <io.h>
#include "softDelay.h"
#include "initPorts.h"
#include "cpuclockinit.h"
#include "led.h"

void cpuClockInit(void)
{

	BCSCTL1 = 0;			// set reg '0000 0000'  XT2 on
	BCSCTL2 = SELM_2 | SELS ;			// set reg '1000 1000'   SMCLK = XT2
	IE1 |= OFIE;			// osc fault interrupt enable

	softDelay(30000);
	IFG1 &= ~OFIFG;			// clear osc fault flag
	softDelay(40000);		// wait 40mS

					// if osc fault still set, hang with blinking led
	if(IFG1 & OFIFG)
	{
		while(1)
		{
			LED1TOGGLE;
			softDelay(3000);
		}
	}
}
