//Functions to operate the wireless module; reading and writing data to module configuration registers, writing data transmit payload, reading data received payload, sending and receiving data packets
#include <io.h>
#include "nRF24L01.h"
#include "spi.h"
#include "softDelay.h"
#include "initPorts.h"
#include "led.h"
#define ADDRSIZE 3
#define PACKETSIZE 32

//static const char address0[3] = {4,2,19};	// ls byte first

static const char address[6][3] = {{4,2,19},{2,2,6},{11,3,12},{6,6,6},{5,15,3},{7,3,8}};
static unsigned char ConfigRegData=0;
static uint8_t rfconfig_copy;

void rfRxMode(void)
{
	ConfigRegData |= PRIM_RX;
	rfWriteReg(REG_CONFIG,ConfigRegData);	// set into RX mode
	RF_CE_HIGH;						//set CE high
}

void rfTxMode(void)
{
	ConfigRegData &= ~PRIM_RX;
	rfWriteReg(REG_CONFIG,ConfigRegData);	// set into TX mode
	RF_CE_HIGH;						//set CE high
	softDelay(20); //CE high for >10uS
	RF_CE_LOW;
}
void rfStandbyMode(void)
{
	RF_CE_LOW;
}
void rfPwrUp(void)
{
	ConfigRegData |= PWR_UP;
	rfWriteReg(REG_CONFIG,ConfigRegData);
}

void rfPwrDown(void)
{
	ConfigRegData &= ~PWR_UP;
	rfWriteReg(REG_CONFIG,rfconfig_copy);
}

void rfInit(void)
{
	P2DIR |= RF_CE_BIT;	// CE is output (1 = RX mode) (P2.4)
	P2DIR &= ~RF_IRQ_BIT;	// IRQ from rf is input (0) (P2.2)
	P2OUT &= ~RF_CE_BIT;	// set CE low (0 = standby mode)
}

void rfWriteReg(unsigned char reg, unsigned char c)
{
	SPI_CSN_LOW;          // chip select, selected (0) (P2.3)
	spiTx(CMD_W_REGISTER | (reg & 0x1f) );	// write reg command
	spiTx(c);            // transmit and recieves a character
	SPI_CSN_HIGH;        // chip select, unselected (1) (P2.3)
}

unsigned char rfGetStatus(void)
{
	unsigned char c;
	SPI_CSN_LOW;
	c = spiTx(0xFF);
	SPI_CSN_HIGH;
	return c;
}

unsigned char rfGetFifoStatus(void)
{
	unsigned char c;
	c = rfReadReg(REG_FIFO_STATUS);
	return c;
}


unsigned char rfReadReg(unsigned char reg)
{
	unsigned char c;
	SPI_CSN_LOW;
	spiTx(CMD_R_REGISTER | reg);
	c = spiTx(0xFF);
	SPI_CSN_HIGH;
	return c;
}


void rfSetAddress(unsigned char addrReg, const char addr[])
{
	int n;
	SPI_CSN_LOW;
	spiTx(CMD_W_REGISTER | addrReg);

	for(n=0; n<ADDRSIZE; n++) {
		spiTx(addr[n]);
	}

	SPI_CSN_HIGH;
}


void rfConfig(void)
{
//	rfInit();	// set up io  - moved to InitPorts as only conig'd ports
	rfWriteReg(REG_EN_AA,0);	// disable auto ack (enabled as default)
	rfWriteReg(REG_EN_RXADDR,1);	// data pipe 0 only
	rfWriteReg(REG_SETUP_AW,1);	// 3 byte address
	rfWriteReg(REG_SETUP_RETR,0);	//disable retries/ReTx
	rfSetAddress(REG_ADDR_P0,address[0]);	// rx address	//My Address is A[0]
	rfSetAddress(REG_TXADDR,address[1]);	// tx address	//Sending to A[1]
	rfWriteReg(REG_RX_PW_P0,PACKETSIZE);	// 32 byte payload
	ConfigRegData = 0x08;	//setup reg data as in PoR
}

int rfGetPacket(volatile unsigned char *buf, unsigned int size)
{
	if(rfReadReg(REG_FIFO_STATUS) & RX_EMPTY) return 0;

	unsigned char nget = rfReadReg(REG_RX_PW_P0);	// number of bytes in pipe
	if(nget < size) size = nget;
	int n = size;


	SPI_CSN_LOW;
	spiTx(CMD_R_RX_PAYLOAD);
	while(n--) {
		*buf++ = spiTx(0xFF);
	}
	SPI_CSN_HIGH;
	rfWriteReg(REG_STATUS,RX_DR);	// clear data ready flag
	return size;
}

/** Send a byte.
Assumes chip is ready to send one.
**/
void rfSendByte(uint8_t c)
{
	int i;
	SPI_CSN_LOW;
	spiTx(CMD_W_TX_PAYLOAD);
	spiTx(c);
	SPI_CSN_HIGH;

	// pulse CE high for > 10uS  causes packet to tx
	RF_CE_HIGH;
	softDelay(15);
	i = 50;
	do (i--);
	while (i != 0);
	RF_CE_LOW;
}

void rfSendByte2Module(unsigned char c)
{
	SPI_CSN_LOW;
	spiTx(CMD_W_TX_PAYLOAD);
	spiTx(c);
	SPI_CSN_HIGH;
}


/** Send a packet.
Assumes chip is ready to send one.
**/
int rfSendPacket(unsigned char *buf, unsigned char count)
{
	if(count > MAX_PKTLEN) count = MAX_PKTLEN;
	int n = count;

	SPI_CSN_LOW;
	spiTx(CMD_W_TX_PAYLOAD);
	while(n--) {
		spiTx(*buf++);
	}
	SPI_CSN_HIGH;

	// pulse CE high for > 10uS
	RF_CE_HIGH;
	softDelay(10);
	RF_CE_LOW;

	return count;
}

int rfSendPacket2Module(unsigned char *buf, unsigned char count)
{
	if(count > MAX_PKTLEN) count = MAX_PKTLEN;
	int n = 0;

	SPI_CSN_LOW;
	spiTx(CMD_W_TX_PAYLOAD);
	while (n < PACKETSIZE)
	{
		spiTx( buf[n] );
		n++;
	}
	SPI_CSN_HIGH;

	return count;
}

void rfFlushRx(void)
{
	while(!(rfReadReg(REG_FIFO_STATUS) & RX_EMPTY)) {
		SPI_CSN_LOW;
		spiTx(CMD_R_RX_PAYLOAD);
		spiTx(0xFF);
		SPI_CSN_HIGH;
	}
	rfWriteReg(REG_STATUS,RX_DR);	// clear data ready flag
}
