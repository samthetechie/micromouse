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



/*-=-=-=-=-=-=-=- GLOBAL VARS -=-=-=-=-=-=-=-=-=-=-=-*/
unsigned int Maze [MAZEY][MAZEX];
unsigned int Mouse=0;				//contains heading and xy position of mouse


//unsigned int count = 0;


int main (void)
{
	unsigned char MoveDir=0;

	SetupCpu();
	SetupCode();
	LED1ON;
	WaitForSwitch();

	AddWall(SOUTH, GetMouseX(), GetMouseY() );
	SetCurrentCellReserved();
	AnalyseCellLR();
	AnalyseCellFB();
	IncrementCellVisits();
	SetThisCellMappedByThisMouse();

	while (1)
	{

		MoveDir=GetExitDir();

		Rotate( MoveDir );

		DriveToEndOfCurrentCellCorrecting();
//WaitForSwitch();
		SetCurrentCellUnreserved();

		MoveToNewCellLogical(MoveDir);		// no walls in new cell, so will not correct until LR analysed

		DriveToStartOfNextCellNOTCorrecting();
//WaitForSwitch();
		AnalyseCellLR();		// analysed, so if walls exist, mouse will correct itself

		SetThisCellMappedByThisMouse();

		DriveToMiddleOfNewCellCorrecting();

		AnalyseCellFB();

		IncrementCellCount();

		IncrementCellVisits();

		DeadEndBlocking();

		if ( IsMazeMapped() ) break;

//WaitForSwitch();






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

	SetLedsUpper (count);

	while (1)
	{
		WaitForSwitch();
		SetLedsUpper(GetLargeErrors());

		WaitForSwitch();
		SetLedsUpper(GetSmallErrors());
	}


	return 0;
}
