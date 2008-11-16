//Functions for reserving and releasing cells
#include <signal.h>
#include "CellReservation.h"
#include "MazeManipulation.h"
#include "Config.h"
#include "RfPacket.h"
#include "nRF24L01.h"
#include "softDelay.h"


extern unsigned int Maze [MAZEY][MAZEX];
extern unsigned char TxPacket[32];
volatile extern unsigned char CTS;

unsigned char GetCellReserved(unsigned char x, unsigned char y)
{
	unsigned char temp = (Maze[y][x] >> 8);
	temp &= 0x0f;
	return temp;
}
void SetCellReserved(unsigned char x, unsigned char y)
{
	unsigned int number = (MOUSENUMBER << 8);	//move mousenumber to correct position
	number &= 0x0F00;	// make sure that mousenumber does not affect any other bits
	Maze[y][x] &= 0xF0FF;	// clear mousenumber bits
	Maze[y][x] |= number;
}

void SetCellReservedByAnotherMouse(unsigned char x, unsigned char y, unsigned char mouse)
{
	unsigned int number = (mouse << 8);	//move mousenumber to correct position
	number &= 0x0F00;	// make sure that mousenumber does not affect any other bits
	Maze[y][x] &= 0xF0FF;	// clear mousenumber bits
	Maze[y][x] |= number;
}




void SetCellUnreserved(unsigned char x, unsigned char y)
{
	Maze[y][x] &= 0xF0FF; // clear bits
}

void SetCurrentCellUnreserved( void )
{
	Maze[GetMouseY()][GetMouseX()] &= 0xF0FF; // clear bits
}


void ReserveCell(unsigned char x,unsigned char y)
{//Cell required, so tell other mice to reserve cells
	SetCellReserved(x,y);
	while(!CTS);
	dint();
	AssembleCellReservePacket(x,y);
	rfStandbyMode();
	rfSendPacket2Module(&TxPacket[0],32);
	rfTxMode();
	eint();
	softDelay(65535);
}

void ReserveCurrentCell(void)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();

	ReserveCell(MouseX,MouseY);
}

unsigned char ReserveCellsAround(unsigned char MoveDir)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	unsigned char Failure = 0x0F;
	//unsigned int number = (MOUSENUMBER << 8);	//move mousenumber to correct position
	/*	Reserve cell for this mouse by putting its mousenumber
	in 3rd Nibble of MAZE (0x0F00 is mask)
	Want to reserve 3 cells around CurrentPos + MoveDir

	Must check first that maze bounds not exceeded (can not reserve cell [-1] or cell [>MAZEX] or [>MAZEY] )
	& Can not reserve cell if already reserved

	*/

	switch(MoveDir)
	{
		case NORTH:
			MouseY--;	//move centre north
			if (MouseY && (!GetCellReserved(MouseX, MouseY-1)) )		//bound check & not already reserved
			{
				ReserveCell(MouseX, MouseY-1);						//reserve north
				Failure &= ~NORTH;
			}
			if ( (MouseX != (MAZEX-1)) && (!GetCellReserved(MouseX+1, MouseY)) )
			{
				ReserveCell(MouseX+1, MouseY);						//reserve east
				Failure &= ~EAST;
			}
			// no need to reserve south as moving from that direction			South
			if (MouseX && (!GetCellReserved(MouseX-1, MouseY)) )
			{
				ReserveCell(MouseX-1, MouseY);						//reserve west
				Failure &= ~WEST;
			}
			break;

		case EAST:
			MouseX++;	//move centre East
			if (MouseY && (!GetCellReserved(MouseX, MouseY-1)) )
			{
				ReserveCell(MouseX, MouseY-1);						//reserve north
				Failure &= ~NORTH;
			}
			if ( (MouseX != (MAZEX-1)) && (!GetCellReserved(MouseX+1, MouseY)) )
			{
				ReserveCell(MouseX+1, MouseY);						//reserve ease
				Failure &= ~EAST;
			}
			if ( (MouseY != (MAZEY-1)) && (!GetCellReserved(MouseX, MouseY+1)) )
			{
				ReserveCell(MouseX, MouseY+1);						//reserve south
				Failure &= ~SOUTH;;
			}
			//no need to reserve west as moving from that direction				West
			break;

		case SOUTH:
			MouseY++;	//move centre south
			//no need to reserve north as moving from that direction			North
			if ((MouseX != (MAZEX-1)) && (!GetCellReserved(MouseX+1, MouseY)) )
			{
				ReserveCell(MouseX+1, MouseY);						//reserve ease
				Failure &= ~EAST;
			}
			if ((MouseY != (MAZEY-1)) && (!GetCellReserved(MouseX, MouseY+1)) )
			{
				ReserveCell(MouseX, MouseY+1);						//reserve south
				Failure &= ~SOUTH;;
			}
			if (MouseX && (!GetCellReserved(MouseX-1, MouseY)) )
			{
				ReserveCell(MouseX-1, MouseY);						//reserve west
				Failure &= ~WEST;
			}
			break;

		case WEST:
			MouseX--;	//move centre west
			if (MouseY && (!GetCellReserved(MouseX, MouseY-1)) )
			{
				ReserveCell(MouseX, MouseY-1);						//reserve north
				Failure &= ~NORTH;;
			}
			//no need to reserve east as moving from that direction				East
			if ((MouseY != (MAZEY-1)) && (!GetCellReserved(MouseX, MouseY+1)) )
			{
				ReserveCell(MouseX, MouseY+1);						//reserve south
				Failure &= ~SOUTH;
			}
			if (MouseX && (!GetCellReserved(MouseX-1, MouseY)) )
			{
				ReserveCell(MouseX-1, MouseY);						//reserve west
				Failure &= ~WEST;
			}
			break;

		default:
			//error
			break;
		}
	return Failure;		//if a cell has not been able to be reserved, this will show it
}



void ReserveCellsAroundHere (void)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	unsigned char Exits = GetExits(MouseX,MouseY);

	/*	Reserve cell for this mouse by putting its mousenumber
	in 3rd Nibble of MAZE (0x0F00 is mask)

	Must check first that maze bounds not exceeded (can not reserve cell [-1] or cell [>MAZEX] or [>MAZEY] )
	& Can not reserve cell if already reserved
	*/


	if (MouseY)
	{
		if ( (!GetCellReserved(MouseX, MouseY-1)) && (Exits & NORTH) )
		{	//bound check & not already reserved & No Wall
			SetCellReserved(MouseX, MouseY-1);						//reserve north
		}
	}
	if ( (MouseX != (MAZEX-1)) )
	{
		if ( (!GetCellReserved(MouseX+1, MouseY))  && (Exits & EAST) )
		{
			SetCellReserved(MouseX+1, MouseY);						//reserve east
		}
	}
	if ( (MouseY != (MAZEY-1)) )
	{
		if ( (!GetCellReserved(MouseX, MouseY+1))  && (Exits & SOUTH) )
		{
			SetCellReserved(MouseX, MouseY+1);						//reserve south
		}
	}
	if (MouseX)
	{
		if ( (!GetCellReserved(MouseX-1, MouseY))  && (Exits & WEST) )
		{
			SetCellReserved(MouseX-1, MouseY);						//reserve west
		}
	}


}

void ReleaseCell(unsigned char x,unsigned char y)
{//Cells not required any more, so tell other mice to unreserve cells
	SetCellUnreserved(x,y);
	while(!CTS);
	dint();
	AssembleCellReleasePacket(x,y);
	rfStandbyMode();
	rfSendPacket2Module(&TxPacket[0],32);
	rfTxMode();
	eint();
	softDelay(65535);
}

void ReleaseCurrentCell(void)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();

	ReleaseCell(MouseX,MouseY);
}

void ReleaseOldCells(unsigned char MoveDir)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	//unsigned char Failure = 0x0F;
	/*
	To release a cell:
		must have already been reserved (by this mouse)
		must be in the maze [such that array indexis not out of bounds etc.]
	*/
	MoveDir = ShiftLeftWrapNibble(ShiftLeftWrapNibble(MoveDir));	//Swap dir [N<==>S], [E<==>W]

	switch(MoveDir)
	{
		case NORTH:
			MouseY--;	//move centre north
			if (MouseY) //North boundary check
			{
				if ( GetCellReserved(MouseX, MouseY-1) == MOUSENUMBER )
				{
					ReleaseCell(MouseX, MouseY-1);						//release north
				}
			}
			if ( (MouseX != (MAZEX-1)) && (GetCellReserved(MouseX+1, MouseY) == MOUSENUMBER) )
			{
				ReleaseCell(MouseX+1, MouseY);						//release east
			}

			//have moved south so don't release								South

			if (MouseX)	//West boundary check
			{
				if ( GetCellReserved(MouseX-1, MouseY) == MOUSENUMBER )
				{
					ReleaseCell(MouseX-1, MouseY);						//release west
				}
			}
			break;

		case EAST:
			MouseX++;	//move centre East
			if (MouseY) //North boundary check
			{
				if ( GetCellReserved(MouseX, MouseY-1) == MOUSENUMBER )
				{
					ReleaseCell(MouseX, MouseY-1);						//release north
				}
			}
			if ( (MouseX != (MAZEX-1)) && (GetCellReserved(MouseX+1, MouseY) == MOUSENUMBER)  )
			{
				ReleaseCell(MouseX+1, MouseY);						//release east
			}
			if ( (MouseY != (MAZEY-1)) && (GetCellReserved(MouseX, MouseY+1) == MOUSENUMBER)  )
			{
				ReleaseCell(MouseX, MouseY+1);						//release south
			}

			//no need to release west as moved to that direction				West
			break;

		case SOUTH:
			MouseY++;	//move centre south
			//no need to release north as moved to that direction			North

			if ( (MouseX != (MAZEX-1)) && (GetCellReserved(MouseX+1, MouseY) == MOUSENUMBER)  )
			{
				ReleaseCell(MouseX+1, MouseY);						//release east
			}
			if ( (MouseY != (MAZEY-1)) && (GetCellReserved(MouseX, MouseY+1) == MOUSENUMBER)  )
			{
				ReleaseCell(MouseX, MouseY+1);						//release south
			}
			if (MouseX)	//West boundary check
			{
				if ( GetCellReserved(MouseX-1, MouseY) == MOUSENUMBER )
				{
					ReleaseCell(MouseX-1, MouseY);						//release west
				}
			}
			break;

		case WEST:
			MouseX++;	//move centre west

			if (MouseY) //North boundary check
			{
				if ( GetCellReserved(MouseX, MouseY-1) == MOUSENUMBER )
				{
					ReleaseCell(MouseX, MouseY-1);						//release north
				}
			}

			//no need to release East as moved to that direction			East

			if ( (MouseY != (MAZEY-1)) && (GetCellReserved(MouseX, MouseY+1) == MOUSENUMBER) )
			{
				ReleaseCell(MouseX, MouseY+1);						//release south
			}
			if (MouseX)	//West boundary check
			{
				if ( GetCellReserved(MouseX-1, MouseY) == MOUSENUMBER )
				{
					ReleaseCell(MouseX-1, MouseY);						//release west
				}
			}
			break;

		default:
			//error
			break;
	}
}

void ReleaseWalledCells (void)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	unsigned char Walls = GetWalls(MouseX,MouseY);

	/*

	Having reserved all cells around destination, some may be unaccessible as
	there is a wall in the way. If so, cell does not need to be reserved, so
	release that cell.
	*/


	if (MouseY) //North boundary check
	{
		if ( (GetCellReserved(MouseX, MouseY-1)) && (Walls & NORTH) )
		{
			ReleaseCell(MouseX, MouseY-1);						//release north
		}
	}
	if ( MouseX != (MAZEX-1) )	//East boundary check
	{
		if( (GetCellReserved(MouseX+1, MouseY))  && (Walls & EAST) )
		{
			ReleaseCell(MouseX+1, MouseY);						//release east
		}
	}
	if ( MouseY != (MAZEY-1) ) //South boundary check
	{
		if ( (GetCellReserved(MouseX, MouseY+1))  && (Walls & SOUTH) )
		{
			ReleaseCell(MouseX, MouseY+1);						//release south
		}
	}
	if (MouseX)	//West boundary check
	{
		if ( (GetCellReserved(MouseX-1, MouseY))  && (Walls & WEST) )
		{
			ReleaseCell(MouseX-1, MouseY);						//release west
		}
	}
}




