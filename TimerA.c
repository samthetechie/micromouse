//Contains functions to initialise, start and stop Timer A
#include "TimerA.h"
#include <io.h>


void TimerAInit ( void )
{		//32.768kHz @ full counter of (2^16) = 0.5 seconds between interrupts	// but emperically looks like 2s
	TACTL = ( TASSEL_1 | TAIE );//| ID_2);	//Div by 4
	TACCTL0 = ( CCIE );
	TACCR0 = 0xFFFF;



}

inline void TimerAStart (void)
{
	TAR=0;
	TACTL |= MC_1;
}

inline void TimerAStop (void)
{
	TACTL &= ~(MC_3);	//Covers all timer count types
}


