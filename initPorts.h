#ifndef INITPORTS_INCL
#define INITPORTS_INCL

//#include <stdint.h>
#include <io.h>

#define SWITCH ((P3IN >> 5) & 1 )


#define LED7ON		P1OUT |=  (1 << 0)	//1
#define LED7OFF		P1OUT &= ~(1 << 0)
#define LED7TOGGLE	P1OUT ^=  (1 << 0)

#define LED5ON		P1OUT |=  (1 << 1)	//2
#define LED5OFF		P1OUT &= ~(1 << 1)
#define LED5TOGGLE	P1OUT ^=  (1 << 1)

#define LED3ON		P1OUT |=  (1 << 2)	//3
#define LED3OFF		P1OUT &= ~(1 << 2)
#define LED3TOGGLE	P1OUT ^=  (1 << 2)

#define LED1ON		P1OUT |=  (1 << 3)	//4
#define LED1OFF		P1OUT &= ~(1 << 3)
#define LED1TOGGLE	P1OUT ^=  (1 << 3)

#define LED2ON		P1OUT |=  (1 << 4)	//5
#define LED2OFF		P1OUT &= ~(1 << 4)
#define LED2TOGGLE	P1OUT ^=  (1 << 4)

#define LED4ON		P1OUT |=  (1 << 5)	//6
#define LED4OFF		P1OUT &= ~(1 << 5)
#define LED4TOGGLE	P1OUT ^=  (1 << 5)

#define LED6ON		P1OUT |=  (1 << 6)	//7
#define LED6OFF		P1OUT &= ~(1 << 6)
#define LED6TOGGLE	P1OUT ^=  (1 << 6)

#define LED8ON		P1OUT |=  (1 << 7)	//0
#define LED8OFF		P1OUT &= ~(1 << 7)
#define LED8TOGGLE	P1OUT ^=  (1 << 7)


/*
#define LED10ON		P4OUT |=  (1 << 7)
#define LED10OFF	P4OUT &= ~(1 << 7)
#define LED10TOGGLE	P4OUT ^=  (1 << 7)

#define LED12ON		P5OUT |=  (1 << 0)
#define LED12OFF	P5OUT &= ~(1 << 0)
#define LED12TOGGLE	P5OUT ^=  (1 << 0)

#define LED14ON		P5OUT |=  (1 << 1)
#define LED14OFF	P5OUT &= ~(1 << 1)
#define LED14TOGGLE	P5OUT ^=  (1 << 1)

#define LED16ON		P5OUT |=  (1 << 2)
#define LED16OFF	P5OUT &= ~(1 << 2)
#define LED16TOGGLE	P5OUT ^=  (1 << 2)

#define LED15ON		P5OUT |=  (1 << 3)
#define LED15OFF	P5OUT &= ~(1 << 3)
#define LED15TOGGLE	P5OUT ^=  (1 << 3)

#define LED13ON		P5OUT |=  (1 << 4)
#define LED13OFF	P5OUT &= ~(1 << 4)
#define LED13TOGGLE	P5OUT ^=  (1 << 4)

#define LED11ON		P5OUT |=  (1 << 5)
#define LED11OFF	P5OUT &= ~(1 << 5)
#define LED11TOGGLE	P5OUT ^=  (1 << 5)

#define LED9ON		P5OUT |=  (1 << 6)
#define LED9OFF		P5OUT &= ~(1 << 6)
#define LED9TOGGLE	P5OUT ^=  (1 << 6)
*/



#define M2P1ON     P5OUT |=  (1 << 3)
#define M2P1OFF    P5OUT &= ~(1 << 3)
#define M2P1TOGGLE P5OUT ^=  (1 << 3)

#define M2P2ON     P5OUT |=  (1 << 0)
#define M2P2OFF    P5OUT &= ~(1 << 0)
#define M2P2TOGGLE P5OUT ^=  (1 << 0)

#define M2P3ON     P5OUT |=  (1 << 2)
#define M2P3OFF    P5OUT &= ~(1 << 2)
#define M2P3TOGGLE P5OUT ^=  (1 << 2)

#define M2P4ON     P5OUT |=  (1 << 1)
#define M2P4OFF    P5OUT &= ~(1 << 1)
#define M2P4TOGGLE P5OUT ^=  (1 << 1)

#define M1P1ON     P5OUT |=  (1 << 6)
#define M1P1OFF    P5OUT &= ~(1 << 6)
#define M1P1TOGGLE P5OUT ^=  (1 << 6)

#define M1P2ON     P5OUT |=  (1 << 5)
#define M1P2OFF    P5OUT &= ~(1 << 5)
#define M1P2TOGGLE P5OUT ^=  (1 << 5)

#define M1P3ON     P5OUT |=  (1 << 7)
#define M1P3OFF    P5OUT &= ~(1 << 7)
#define M1P3TOGGLE P5OUT ^=  (1 << 7)

#define M1P4ON     P5OUT |=  (1 << 4)
#define M1P4OFF    P5OUT &= ~(1 << 4)
#define M1P4TOGGLE P5OUT ^=  (1 << 4)


// RF i/o bits
#define RF_CE_BIT (1 << 4)
#define RF_CE_HIGH (P2OUT |= RF_CE_BIT)
#define RF_CE_LOW (P2OUT &= ~RF_CE_BIT)

#define RF_IRQ_BIT (1 << 2)
#define RF_IRQ_HIGH (P2IN & RF_IRQ_BIT)
#define RF_IRQ_EDGE (P2IFG & RF_IRQ_BIT)
#define RF_IRQ_EDGE_CLEAR (P2IFG &= ~RF_IRQ_BIT)



// prototypes

void PortsInit(void);



#endif

