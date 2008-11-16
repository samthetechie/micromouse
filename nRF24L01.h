#ifndef NRF24L01_INCL
#define NRF24L01_INCL

/*file rf24l01.h
Register definitions for Nordic nRF24L01

*/

#define MAX_PKTLEN 32	// max packet size in use

// Commands
#define CMD_W_REGISTER 		0x20	//Write Command and status registers (only in PwrDn or StandBy modes)
#define CMD_R_REGISTER 		0		//Read CMD and Status Registers
#define CMD_R_RX_PAYLOAD 	0x61	//Read RX Payload
#define CMD_W_TX_PAYLOAD 	0xA0	//Write TX Payload
#define CMD_FLUSH_RX 		0xE2	//Flush RX FIFO
#define CMD_FLUSH_TX 		0xE1	//Flush RX FIFO

// Registers					//Register Maps
#define REG_CONFIG 		  0		//Configuration Register Add = 0x00
#define REG_EN_AA 		  1		//Auto Ack Register Add = 0x01
#define REG_EN_RXADDR 	  2		//Enable RX Addresses Register Add = 0x02
#define REG_SETUP_AW 	  3		//Setup of Address Widths Add = 0x03
#define REG_SETUP_RETR 	  4		//Setup of Automatic Retransmission Add = 0x04
#define REG_RF_CH 		  5		//RF Channel Frequency Add = 0x05
#define REG_RF_SETUP 	  6		//RF Setup Register
#define REG_STATUS 		  7		//Status Register (in parallel to SPI command word on MOSI, data is shifted serially out one MISO pin
#define REG_ADDR_P0 	0x0A	//Recieve Address data pipe 0
#define REG_TXADDR 		0x10	//Transmit Address
#define REG_RX_PW_P0 	0x11	//Pipe width - number of bytes in RX payload in data pipe 0 [1-32 Bytes]
#define REG_FIFO_STATUS 0x17	//FIFO Status Register

// CONFIG register
#define MASK_RX_DR 	(1 << 6)	//Mask RX_DR Interrupt on IRQ
#define MASK_TX_DS 	(1 << 5)	//Mask TX_DR Interrupt on IRQ
#define MASK_MAX_RT (1 << 4)	//Mask MAX_RT Interrupt on IRQ
#define EN_CRC 		(1 << 3)	//Enable CRC
#define CRCO 		(1 << 2)	//CRC Encoding
#define PWR_UP 		(1 << 1)	//Power Up / Down - (1=PwrUP, 0=PwrDn)
#define PRIM_RX 	(1 << 0)	//RX / TX - (1=RX, 0=TX)

// STATUS register
#define RX_DR 	(1 << 6)		//Data Ready RX FIFO Interrupt
#define TX_DS 	(1 << 5)		//Data Sent TX FIFO Interrupt
#define MAX_RT	(1 << 4)		//Max retransmits reached
#define TX_FULL (1 << 0)		//TX FIFO full flag

// FIFO STATUS register
#define FIFO_STATUS_TX_FULL 	(1 << 5)		//TX FIFO FULL flag
#define FIFO_STATUS_TX_EMPTY 	(1 << 4)		//TX FIFO Empty Flag
#define FIFO_STATUS_RX_FULL 	(1 << 1)		//FX FIFO Full Flag
#define RX_EMPTY 				(1 << 0)		//RX FIFO empty flag


// config values for remote and headset
#define REMOTE_CONFIG 	(MASK_RX_DR | MASK_MAX_RT | EN_CRC)
#define HEADSET_CONFIG 	(MASK_TX_DS | MASK_MAX_RT | PRIM_RX | EN_CRC)



//Function Prototypes

#define DCOMULTIPLIER 976

// spi functions in spi.c
void spi_init(void);
void spi_tx(unsigned char c);
unsigned char spi_rx(void);

// rf
void rfConfig(void);
void rfPwrUp(void);
void rfPwrDown(void);
void rfRxMode(void);
void rfTxMode(void);
void rfStandbyMode(void);


int rfGetPacket(volatile unsigned char *buf, unsigned int count);
unsigned char rfGetStatus(void);
unsigned char rfGetFifoStatus(void);

void rfInit(void);
void rfWriteReg(unsigned char reg, unsigned char c);

unsigned char rfReadReg(unsigned char reg);
int rfSendPacket(unsigned char *buf, unsigned char count);
void rfSendByte(unsigned char c);
void rfFlushRx(void);
void rfSetAddress(unsigned char addrReg, const char addr[]);

void rfSendByte2Module(unsigned char c);
int rfSendPacket2Module(unsigned char *buf, unsigned char count);



#endif
