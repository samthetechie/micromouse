#include <signal.h>
#include "MapMaze.h"
#include "MazeManipulation.h"
#include "Config.h"
#include "led.h"
#include "DeadEndBlocking.h"
#include "Setup.h"
#include "Alignment.h"
#include "Motor2.h"
#include "softDelay.h"
#include "CellReservation.h"
#include "RfPacket.h"
#include "nRF24L01.h"
#include "initPorts.h"

static unsigned int CellCount = 1;
extern unsigned char TxPacket[32];
volatile extern unsigned char CTS;

void SetCellCount(unsigned int Ccount)
{
	CellCount = Ccount;
}

unsigned int GetCellCount( void )
{
	return CellCount;
}


void IncrementCellVisits (void)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	unsigned char Visits = GetVisits(MouseX,MouseY);

	SetVisits(MouseX,MouseY,Visits+1);
}


void IncrementCellCount (void)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	unsigned char Visits = GetVisits(MouseX,MouseY);

	if (!Visits) SetCellCount( GetCellCount() + 1 );
}


void AnalyseCellLR (void)
{
	unsigned char MouseHeading = GetMouseHeading();
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	unsigned char Visits = GetVisits(MouseX,MouseY);

	if (!Visits )		//if no visits to cell
	{
		if (MouseHeading == NORTH)
		{
			if (IsWallLeft()) AddWall(WEST,MouseX,MouseY);		//	LED12ON;
			if (IsWallRight()) AddWall(EAST,MouseX,MouseY);		//	LED10ON;
		}
		if (MouseHeading == EAST)
		{
			if (IsWallLeft()) AddWall(NORTH,MouseX,MouseY);
			if (IsWallRight()) AddWall(SOUTH,MouseX,MouseY);
		}
		if (MouseHeading == SOUTH)
		{
			if (IsWallLeft()) AddWall(EAST,MouseX,MouseY);
			if (IsWallRight()) AddWall(WEST,MouseX,MouseY);
		}
		if (MouseHeading == WEST)
		{
			if (IsWallLeft()) AddWall(SOUTH,MouseX,MouseY);
			if (IsWallRight()) AddWall(NORTH,MouseX,MouseY);
		}
	}
}


void AnalyseCellFB (void)
{
	unsigned char MouseHeading = GetMouseHeading();
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	unsigned char Visits = GetVisits(MouseX,MouseY);

	if (!Visits )		//if no visits to cell
	{
		SetThisCellMappedByThisMouse();
		if (MouseHeading == NORTH)
		{
			if (IsWallFront()) AddWall(NORTH,MouseX,MouseY);	//	LED9ON;
			if (IsWallBack()) AddWall(SOUTH,MouseX,MouseY);		//	LED11ON;
		}
		if (MouseHeading == EAST)
		{
			if (IsWallFront()) AddWall(EAST,MouseX,MouseY);
			if (IsWallBack()) AddWall(WEST,MouseX,MouseY);
		}
		if (MouseHeading == SOUTH)
		{
			if (IsWallFront()) AddWall(SOUTH,MouseX,MouseY);
			if (IsWallBack()) AddWall(NORTH,MouseX,MouseY);
		}
		if (MouseHeading == WEST)
		{
			if (IsWallFront()) AddWall(WEST,MouseX,MouseY);
			if (IsWallBack()) AddWall(EAST,MouseX,MouseY);
		}
	}
}

unsigned char GetExitDir (void)
{
	unsigned char MouseY = GetMouseY();
	unsigned char MouseX = GetMouseX();
	unsigned char n=0xFF;
	unsigned char s=0xFF;
	unsigned char e=0xFF;
	unsigned char w=0xFF;
	unsigned char Walls=GetWalls(MouseX,MouseY);
	unsigned char Exits=( (~Walls)&(0xF) );
	unsigned char ne=0; //smallest between n&e
	unsigned char sw=0;//smallest between s&w
	unsigned char nesw=0;//smallest between ne&sw
	unsigned char move = 0; //dir to move
	unsigned char rn = MOUSENUMBER & GetCellReserved(MouseX, MouseY-1);	// reserved north
	unsigned char rs = MOUSENUMBER & GetCellReserved(MouseX, MouseY+1);
	unsigned char re = MOUSENUMBER & GetCellReserved(MouseX+1, MouseY);
	unsigned char rw = MOUSENUMBER & GetCellReserved(MouseX-1, MouseY);	// reserved west

	if (Exits & NORTH)
	{
		if (rn)
		{
			n= (GetVisits(MouseX,MouseY-1)<<4) | NORTH;
		}
	}
	if (Exits & EAST)
	{
		if (re)
		{
			e= (GetVisits(MouseX+1,MouseY)<<4) | EAST;
		}
	}
	if (Exits & SOUTH)
	{
		if (rs)
		{
			s= (GetVisits(MouseX,MouseY+1)<<4) | SOUTH;
		}
	}
	if (Exits & WEST)
	{
		if (rw)
		{
			w= (GetVisits(MouseX-1,MouseY)<<4) | WEST;
		}
	}

	if ( (n==0xFF) && (e==0xFF) && (s==0xFF) && (w==0xFF) )
	{
		//do something like wait and re-do GED()
		LED8ON;
		softDelay(65535);
		LED8OFF;
		softDelay(65535);
		return 0;
	}

	ne = 	(n <= e )	? n : e ;
	sw = 	(s <= w )	? s : w ;
	nesw = 	(ne <= sw)	? ne : sw ;
	move = (nesw & 0xF);

	if (move == NORTH)	SetCellReserved(MouseX, MouseY-1);
	if (move == EAST)	SetCellReserved(MouseX+1, MouseY);
	if (move == SOUTH)	SetCellReserved(MouseX, MouseY+1);
	if (move == WEST)	SetCellReserved(MouseX-1, MouseY);

	return move;
}

void Rotate (unsigned char dir)		// does the mouse need to rotate to exit in the required dir?
{
	unsigned char Heading = GetMouseHeading();

	if (Heading == dir) return;

	else if (Heading == (ShiftLeftWrapNibble(dir)) )	// need to turn 90deg Right
	{
		DriveSpotRotateLeftHalf(DEGREES90);
	}
	else if (Heading == (ShiftRightWrapNibble(dir)) )	// need to turn 90deg Left
	{
		DriveSpotRotateRightHalf(DEGREES90);
	}
	else if (Heading == (ShiftRightWrapNibble(ShiftRightWrapNibble(dir))) ) // need to turn 180 Deg
	{
		DriveSpotRotateLeftHalf(DEGREES180);
	}

	SetMouseHeading(dir);
}



void MoveToNewCellLogical (unsigned char dir)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();

	if (  dir == NORTH ) MouseY--;//North
	if (  dir == EAST  ) MouseX++;//East
	if (  dir == SOUTH ) MouseY++;//South
	if (  dir == WEST  ) MouseX--;//West

	SetMouseX(MouseX);
	SetMouseY(MouseY);
}


unsigned char IsMazeMapped (void)
{
	unsigned int CurrentCellCount = GetCellCount();
	unsigned int MaxCells = (MAZEX) * (MAZEY);

	//SetLedsLower( ((unsigned char)CurrentCellCount) | (((unsigned char)MaxCells) << 4 ) );


	if (CurrentCellCount >= MaxCells)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void DriveToEndOfCurrentCellCorrecting (void)
{
	DriveForwardsHalf(5,1);
}

void DriveToStartOfNextCellNOTCorrecting (void)
{
	DriveForwardsHalf(12,0);
}

void DriveToMiddleOfNewCellCorrecting (void)
{
	DriveForwardsHalf(25,1);
}

void TxCellInfo (void)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	while(!CTS);
	dint();
	AssembleMazePacket (MouseX,MouseY);
	rfStandbyMode();
	rfSendPacket2Module(&TxPacket[0],32);
	rfTxMode();
	eint();

}


