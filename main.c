#include <io.h>

#include "softDelay.h"
#include "led.h"
#include "MapMaze.h"
#include "Setup.h"
#include "Config.h"
#include "MazeManipulation.h"
#include "adc.h"
#include "MazeSolving.h"
#include "Motor2.h"
#include "DeadEndBlocking.h"
#include "Alignment.h"
#include "initPorts.h"
#include "nRF24L01.h"
#include "TimerA.h"
#include "RfPacket.h"
#include "CellReservation.h"

/*-=-=-=-=-=-=-=- GLOBAL VARS -=-=-=-=-=-=-=-=-=-=-=-*/
unsigned int Maze [MAZEY][MAZEX];
unsigned int Mouse=0;				//contains heading and xy position of mouse
volatile unsigned char RF=0;
volatile unsigned char RxPacket[32];
unsigned char TxPacket[32];
volatile unsigned char CTS = 0;
volatile unsigned char TimerExpired=0;

//unsigned int count = 0;


int main (void)
{
	unsigned char MoveDir=0;

	SetupCpu();
	SetupCode();
	rfPwrUp();
	rfRxMode();
	LED1ON;
	WaitForSwitch();
	LED1OFF;
//TimerAStart();


/*
while(1)
{
	if (CTS)
	{
		LED5TOGGLE;
	}
	if (!CTS) LED5OFF;
	if( TimerExpired || IfSwitch() )
	{
		CTS=0;
		TimerExpired=0;
		AssembleStartTimerPacket();
		rfStandbyMode();
		rfSendPacket2Module(&TxPacket[0],32);
		rfTxMode();
		softDelay(65535);
		rfStandbyMode();
		rfRxMode();
		LED1TOGGLE;
	}
}
*/






//	MAZE MAPPING CODE
	AddWall(SOUTH, GetMouseX(), GetMouseY() );
	ReserveCurrentCell();
	AnalyseCellLR();
	AnalyseCellFB();
	ReserveCellsAroundHere();
	IncrementCellVisits();
	SetThisCellMappedByThisMouse();
	TxCellInfo();

	while (1)
	{


		MoveDir = 0;

		while (!MoveDir) //If unable to get an exit, redo until can get exit
		{
			MoveDir=GetExitDir();
			LED7ON;
		}
		LED7OFF;

		ReserveCellsAround(MoveDir);

		Rotate( MoveDir );

		DriveToEndOfCurrentCellCorrecting();

		MoveToNewCellLogical(MoveDir);		// no walls in new cell, so will not correct until LR analysed

		DriveToStartOfNextCellNOTCorrecting();

		AnalyseCellLR();		// analysed, so if walls exist, mouse will correct itself

		DriveToMiddleOfNewCellCorrecting();

		AnalyseCellFB();

		IncrementCellCount();

		IncrementCellVisits();

		TxCellInfo();

		ReleaseOldCells(MoveDir);

		ReleaseWalledCells();

		DeadEndBlocking();

		if ( IsMazeMapped() ) break;


	}

	SetLedsLower(0x55);


		// count total visits in maze

	unsigned char x = 0;
	unsigned char y = 0;
	unsigned char count = 0;

	while (y < MAZEY)
	{
		while (x < MAZEX)
		{
			count += GetVisits(x,y);
			x++;
		}
		y++;
		x=0;
	}

//	SetLedsUpper (count);

	while (1)
	{
		WaitForSwitch();
//		SetLedsUpper(GetLargeErrors());

		WaitForSwitch();
//		SetLedsUpper(GetSmallErrors());
	}


	return 0;
}
