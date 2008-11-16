//Functions to setup, transmit and receive data over the SPI interface
#include <io.h>
#include "spi.h"
#include "softDelay.h"

/** \file spi.c
*/

/** Initialise spi interface on uart0.
Set for 8 bits data, master, 3 pin mode.
Uses SMCLK with divide set to 2 (ie maximum speed). Interrupts disabled.
*/

void spiInit(void)
{
	U0CTL = 0x17;	// SPI, 8 bit data, no loopback, SPI mode, master, reset
	U0TCTL = 0xa3;	// CKPH=1, CKPL=0, SMCLK, 3 pin mode, Tx empty

	U0BR0 = 2;	// smclk divider
	U0BR1 = 0;
	U0MCTL = 0;	// not used, but should be 0

	IE1 &= ~0x80;	// disable interrupts
	IE1 &= ~0x40;

	ME1 |= 0x40;	// enable spi module
	U0CTL &= ~1;	// release reset
}
