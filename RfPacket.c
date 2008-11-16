#include "RfPacket.h"
#include "MazeManipulation.h"
#include "Config.h"
#include "TimerA.h"
#include "CellReservation.h"
#include "MapMaze.h"
#include "initPorts.h"
#include "softDelay.h"

extern volatile unsigned char CTS;
extern volatile unsigned char RxPacket[32];
volatile unsigned char LEDS;

/*
Assembling packet:
B0 = Length
B1 = Packet Type
B2 = From Address
B3 --> Bn = data
B31 Last byte - packet cannot be longer than 32 bytes.
*/

/*
Packet Types:
01:Maze Packet
02:Cell Reserve
03:Cell Release
04:
05:Start Synchronised Timers
06:CTS
07:TestData Packet
08:Start Timer


*/


extern unsigned char TxPacket[32];

//Maze packet Type = 1
void AssembleMazePacket (unsigned char x, unsigned char y)
{
	//In a maze packet:
		//B0 = Length
		//B1 = Packet Type
		//B2 = From Address [mousenumber]
		//B3 = xCoord
		//B4 = yCoord
		//B5 = Visits
		//B6 = Cell Reserved by Mouse
		//B7 = Mapped by Mouse
		//B8 = Walls

	TxPacket[0] = 9;		// this packet contains 9 bytes (including this one)
	TxPacket[1] = 0x01;	// Maze Packet
	TxPacket[2] = MOUSENUMBER;
	TxPacket[3] = x;
	TxPacket[4] = y;
	TxPacket[5] = GetVisits(x,y);
	TxPacket[6] = GetCellReserved(x,y);		//redundant
	TxPacket[7] = GetCellMappedBy(x,y);
	TxPacket[8] = GetWalls(x,y);

	unsigned char count = 9;	//set rest of bytes to 0
	while (count < 32)
	{
		TxPacket[count]=0;	//set to 0
		count++;
	}
}

// Reserve Cell Packet Type = 2
void AssembleCellReservePacket (unsigned char x, unsigned char y)
{
	//In a CellReserve packet:
		//B0 = Length
		//B1 = Packet Type
		//B2 = From Address [mousenumber]
		//B3 = xCoord
		//B4 = yCoord

	TxPacket[0] = 5;		// this packet contains 5 bytes (including this one)
	TxPacket[1] = 0x02;		// CellReserve Packet
	TxPacket[2] = MOUSENUMBER;
	TxPacket[3] = x;
	TxPacket[4] = y;


	unsigned char count = 5;	//set rest of bytes to 0
	while (count < 32)
	{
		TxPacket[count]=0;	//set to 0
		count++;
	}
}
//	Cell Release Packet Type = 3
void AssembleCellReleasePacket(unsigned char x, unsigned char y)
{
	//In a CellRelease packet:
		//B0 = Length
		//B1 = Packet Type
		//B2 = From Address [mousenumber]

	TxPacket[0] = 5;		// this packet contains 5 bytes (including this one)
	TxPacket[1] = 0x03;		// Cell Release Packet
	TxPacket[2] = MOUSENUMBER;
	TxPacket[3] = x;
	TxPacket[4] = y;

	unsigned char count = 5;	//set rest of bytes to 0
	while (count < 32)
	{
		TxPacket[count]=0;	//set to 0
		count++;
	}


}

// Cell  Packet Type = 4	UNUSED

// StartSynchronisedTimers Packet Type = 5
void AssembleStartSynchronisedTimersPacket(unsigned char x, unsigned char y, unsigned char reply)
{
	//In a CellReserveRequestReply packet:
		//B0 = Length
		//B1 = Packet Type
		//B2 = From Address [mousenumber]

	TxPacket[0] = 6;		// this packet contains 6 bytes (including this one)
	TxPacket[1] = 0x05;		// StartSynchronisedTimers
	TxPacket[2] = MOUSENUMBER;
	TxPacket[3] = x;
	TxPacket[4] = y;
	TxPacket[5] = reply;

	unsigned char count = 6;	//set rest of bytes to 0
	while (count < 32)
	{
		TxPacket[count]=0;	//set to 0
		count++;
	}
}

// CTS Packet Type = 6
void AssembleCTSPacket(void)
{
	//In a CellReserveRequestReply packet:
		//B0 = Length
		//B1 = Packet Type
		//B2 = From Address [mousenumber]

	TxPacket[0] = 3;		// this packet contains 3 bytes (including this one)
	TxPacket[1] = 0x06;		// CTS packet
	TxPacket[2] = MOUSENUMBER;

	unsigned char count = 3;	//set rest of bytes to 0
	while (count < 32)
	{
		TxPacket[count]=0;	//set to 0
		count++;
	}

}

// Test Data Packet Type = 7
void AssembleTestDataPacket(unsigned char data)
{
	//In a CellReserveRequestReply packet:
		//B0 = Length
		//B1 = Packet Type
		//B2 = From Address [mousenumber]

	TxPacket[0] = 4;		// this packet contains 4 bytes (including this one)
	TxPacket[1] = 0x07;		// CTS packet
	TxPacket[2] = MOUSENUMBER;
	TxPacket[3] = data;

	unsigned char count = 4;	//set rest of bytes to 0
	while (count < 32)
	{
		TxPacket[count]=0;	//set to 0
		count++;
	}

}

// StartTimer Packet Type = 8
void AssembleStartTimerPacket( void )
{
	//In a CellReserveRequestReply packet:
		//B0 = Length
		//B1 = Packet Type
		//B2 = From Address [mousenumber]

	TxPacket[0] = 3;		// this packet contains 3 bytes (including this one)
	TxPacket[1] = 0x08;		// StartTimer
	TxPacket[2] = MOUSENUMBER;


	unsigned char count = 3;
	while (count < 32)
	{
		TxPacket[count]=0;
		count++;
	}

}






























void DisassemblePacket(void)
{

	switch(RxPacket[1])
	{
		case 0:
			break;

		case 1:		//Maze Packet
			//TxPacket[2] = MOUSENUMBER;
			//TxPacket[3] = x;
			//TxPacket[4] = y;
			//TxPacket[5] = GetVisits(x,y);
			//TxPacket[6] = GetCellReserved(x,y);	//redundant
			//TxPacket[7] = GetCellMappedBy(x,y);
			//TxPacket[8] = GetWalls(x,y);

			if ( !GetVisits(RxPacket[3],RxPacket[4]) )		// if already mapped, do not need to re-map
			{
				SetWalls ( RxPacket[3],RxPacket[4],RxPacket[8] );
				SetCellMappedBy( RxPacket[3],RxPacket[4],RxPacket[7] );
				SetCellCount( GetCellCount() + 1);
			}
			SetVisits( RxPacket[3],RxPacket[4],RxPacket[5] );

			break;

		case 2:		//CellReserve Packet
			SetCellReserved(RxPacket[3],RxPacket[4]);
			break;

		case 3:		//Cell Release Packet
			SetCellUnreserved(RxPacket[3],RxPacket[4]);
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:		//CTS packet
			CTS = 1;
			LED6ON;
			LED7ON;
			LED8ON;
			softDelay(65535);
			LED6OFF;
			LED7OFF;
			LED8OFF;
			TimerAStart();
			break;
		case 7:		//Test Data packet
			LEDS = RxPacket[3];
			break;
		case 8:		//Start Timer Instruction
			CTS=1;
			TimerAStart();
			break;


		default:
			break;

	}




}





