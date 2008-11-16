#ifndef SPI_INCL
#define SPI_INCL

/** \file spi.h
Function prototypes and in-line functions for spi handling.

There's no need for an Rx function, since have to send
something on SPI in order to get something back.
*/

void spiInit(void);			// initialises spi port

/** Send a byte to spi and return byte received on spi.

\param c - byte to send to SPI.

*/

// spi port assignments
#define SPI_CSN_BIT (1 << 3)
#define SPI_MOSI_BIT (1 << 1)
#define SPI_MISO_BIT (1 << 2)
#define SPI_SCK_BIT (1 << 3)

// spi i/o control
#define SPI_CSN_HIGH (P2OUT |= SPI_CSN_BIT)
#define SPI_CSN_LOW  (P2OUT &= ~SPI_CSN_BIT)

#define SPI_MOSI_HIGH (P3OUT |= SPI_MOSI_BIT)
#define SPI_MOSI_LOW  (P3OUT &= ~SPI_MOSI_BIT)

#define SPI_MISO (P3IN & SPI_MISO_BIT)

#define SPI_SCK_HIGH (P3OUT |= SPI_SCK_BIT)
#define SPI_SCK_LOW (P3OUT &= ~SPI_SCK_BIT)

#define SPICLOCK { SPI_SCK_HIGH; SPI_SCK_LOW; }



static inline unsigned int spiTx(unsigned char c)
{
	while(!(IFG1 & UTXIFG0));	// wait for tx buffer empty
	U0TXBUF = c;

	while(!(IFG1 & URXIFG0));	// wait for response
	return U0RXBUF;
}

/** Disable the spi module (for power saving).
*/

static inline void spiOff(void)
{
	ME1 &= ~0x40;	// disable spi module
}

/** Send a byte to the spi but don't return anything.
This is quicker than spiTx() but leaves
a character in the spi rx buffer. Also, the transmit may not have completed before the
function returns, so make sure to check it's all been sent before disabling or
deselecting the spi.
*/
static inline void spiTxQuick(unsigned char c)
{
	while(!(IFG1 & UTXIFG0));	// wait for tx buffer empty
	U0TXBUF = c;
}

/** Macro to test if spi transmission has finished.
\return 1 if tx buffer is empty (ie transmission finished), 0 otherwise.
*/

#define SPI_TXDONE (U0TCTL & TXEPT)

/** Macro to clear byte ready flag in spi receive register.
Useful after a series of spiTxQuick calls,
when there will be a character in the buffer which you probably don't want.
*/

#define SPI_RXCLEAR IFG1 &= ~URXIFG0

#endif
