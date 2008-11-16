//Not implemented; contains functions to instruct robot to move to a particular cell after maze has been mapped, using a flooding algorithm
#include "MazeSolving.h"
#include "Config.h"
#include "MazeManipulation.h"
#include "Error.h"
#include "Motor2.h"

unsigned int FloodMaze [MAZEY][MAZEX];

static unsigned int GetFloodHere ( void );
static unsigned int GetFlood ( unsigned char, unsigned char );
static void SetFloodHere ( unsigned int );
static void SetFlood( unsigned char, unsigned char, unsigned int );

static unsigned int GetFloodHere ( void )
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();

	return FloodMaze[MouseY][MouseX];
}

static unsigned int GetFlood ( unsigned char MazeX, unsigned char MazeY )
{
	return FloodMaze[MazeY][MazeX];
}

static void SetFloodHere ( unsigned int FloodValue )
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();

	if(FloodValue > 0xFFF) ThrowError(1);

	FloodMaze[MouseY][MouseX] = FloodValue;
}

static void SetFlood (unsigned char MazeX, unsigned char MazeY, unsigned int FloodValue )
{
	if(FloodValue > 0xFFF) ThrowError(2);
	FloodMaze[MazeY][MazeX] = FloodValue;
}

static void InitFlood ( void )
{//clear out old flooding and set all to zero
	int x = 0;
	int y = 0;

	while (y < MAZEY)
	{
		while (x < MAZEX)
		{
			SetFlood(x,y,0);
			x++;
		}
		y++;
		x=0;
	}
}




void DoMazeFlooding ( void )
{

	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	int x = 0;
	int y = 0;
	unsigned int CurrentFlood = 1;
	unsigned char Exits = 0;

	InitFlood();
	SetFlood(TARGETX,TARGETY,1);	// set target cell flood value =1

	while ( ! GetFlood( MouseX, MouseY ) )	// while mouse's cell is not flooded
	{
		x=0;
		y=0;
		while (y < MAZEY)//loop through all sells
		{
			while (x < MAZEX)
			{
				if ( GetFlood( x, y ) == CurrentFlood)
				{
					//SetUnflooded exits to CFV+1
					Exits = GetExits( x, y );
					if ( (Exits & NORTH)	&& ( ! GetFlood(x,(y-1)) ) ) 	SetFlood( x, (y-1), (CurrentFlood +1) );
					if ( (Exits & EAST) 	&& ( ! GetFlood((x+1),y) ) ) 	SetFlood( (x+1), y, (CurrentFlood +1) );
					if ( (Exits & SOUTH) 	&& ( ! GetFlood(x,(y+1)) ) ) 	SetFlood( x, (y+1), (CurrentFlood +1) );
					if ( (Exits & WEST) 	&& ( ! GetFlood((x-1),y) ) ) 	SetFlood( (x-1), y, (CurrentFlood +1) );
				}
				x++;
			}
			y++;
			x=0;
		}
		CurrentFlood++;
		if (CurrentFlood > 0xFFF) ThrowError(3);
	}
}



unsigned char MoveFollowFloodedMaze ( void )
{
	unsigned char MouseY = GetMouseY();
	unsigned char MouseX = GetMouseX();
	unsigned int n=0xFFFF;
	unsigned int s=0xFFFF;
	unsigned int e=0xFFFF;
	unsigned int w=0xFFFF;
	unsigned char Walls=GetWalls(MouseX,MouseY);
	unsigned char Exits=( (~Walls)&(0xF) );
	unsigned int ne=0; //smallest between n&e
	unsigned int sw=0;//smallest between s&w
	unsigned int nesw=0;//smallest between ne&sw
	unsigned char move = 0; //dir to move




	if (Exits & NORTH)	n = ( (GetFlood(MouseX,MouseY-1)<<4) | NORTH);
	if (Exits & EAST)	e = ( (GetFlood(MouseX+1,MouseY)<<4) | EAST);
	if (Exits & SOUTH)	s = ( (GetFlood(MouseX,MouseY+1)<<4) | SOUTH);
	if (Exits & WEST)	w = ( (GetFlood(MouseX-1,MouseY)<<4) | WEST);


	if ( (n==0xFFFF) && (e==0xFFFF) && (s==0xFFFF) && (w==0xFFFF) ) ThrowError(4);

	ne = 	(n <= e )	? n : e ;
	sw = 	(s <= w )	? s : w ;
	nesw = 	(ne <= sw)	? ne : sw ;
	move = (unsigned char)(nesw & 0xF);

	return move;
}

void MoveFloodHalfCellCorrecting ( void )
{

	DriveForwardsFull(HALFCELL,1);	//Move half cell with corrections

}



unsigned char MouseArrived ( void )
{
	unsigned char MouseY = GetMouseY();
	unsigned char MouseX = GetMouseX();


	if ( (MouseX == TARGETX) && (MouseY ==TARGETY) ) return 1;
	else return 0;
}















