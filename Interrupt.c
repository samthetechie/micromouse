#include <signal.h>
#include <io.h>
#include <iomacros.h>
#include "Interrupt.h"
//#include "led.h"
#include "initPorts.h"
#include "nRF24L01.h"
#include "softDelay.h"
#include "TimerA.h"
#include "RfPacket.h"

//extern volatile unsigned char RF;
extern volatile unsigned char CTS;
extern unsigned char TxPacket[32];
extern volatile unsigned char RxPacket[32];
extern volatile unsigned char TimerExpired;

void InitInterrupt (void)
{
	eint();

}


interrupt (PORT2_VECTOR) p2_interrupt(void)		// interrupts enabled on P2.2, H2L transition [\]
{
	unsigned char c=0;
	while( !(P2IN & (1<<2)) )
	{
		c = (rfGetStatus() & (0x70) );	//3 interrupt bits are 4,5,6		msb[0111|0000]lsb = 0x70
										//6: Data Ready on RX {RX_DR}
										//5: Data Sent (on receipt of ACK, if ACK enabled) {TX_DS}
										//4: Max Retransmit occured {MAX_RT}

		if(c & MAX_RT)
		{
			rfWriteReg(REG_STATUS,MAX_RT);	//write 1 to clear bit on nRF[yes, I know, but that's what is says!!]
			rfSendPacket2Module(&TxPacket[0], 32);
			rfStandbyMode();
			rfTxMode();
		}
		if(c & TX_DS)	//data sent
		{
			rfStandbyMode();
			rfWriteReg(REG_STATUS,TX_DS);	//write 1 to clear bit on nRF[yes, I know, but that's what is says!!]
			rfRxMode();		//After sent packet go to RX mode
			LED2ON;
			softDelay(65535);
			LED2OFF;
		}
		if(c & RX_DR)	//data ready
		{
			rfStandbyMode();
			rfWriteReg(REG_STATUS,RX_DR);	//write 1 to clear bit on nRF[yes, I know, but that's what is says!!]
			//RF=1;
			rfGetPacket(&RxPacket[0], 32);
			rfRxMode();
			DisassemblePacket();
			LED3ON;
			softDelay(65535);
			LED3OFF;
		}
	}
	P2IFG = 0;	//clear all port2 interrupt flags on MCU
}


interrupt (TIMERA0_VECTOR) TimerA0Interrupt(void)
{// vector for 'TACCR0 CCIFG' - on count to value in TACCR0
// Flag is automatically reset when interrupt is serviced
	TimerAStop();
//	TimerExpired=1;
	CTS=0;
//	TimerExpired=0;
	AssembleStartTimerPacket();
	rfStandbyMode();
	rfSendPacket2Module(&TxPacket[0],32);
	rfTxMode();
	softDelay(65535);
	rfStandbyMode();
	rfRxMode();


}

interrupt (TIMERA1_VECTOR) TimerA1Interrupt(void)
{// vector for 'TACCR1 CCIFG' & 'TACCR2 CCIFG' & 'TAIFG'(overflow)
// Accessing register (R or W) resets the highest interrupt
	unsigned char TimerAIntReg = TAIV;

	if (TimerAIntReg & TAIV_CCR1)	//Capture Compare Register 1
	{
		return;
	}
	if (TimerAIntReg & TAIV_CCR2)	//Capture Compare Register 2
	{
		return;
	}
	if (TimerAIntReg & TAIV_OVERFLOW)	//count to zero
	{
		return;
	}

	// should never get to here as ISR is only called when one of the above 3 is true!
	return;
}




