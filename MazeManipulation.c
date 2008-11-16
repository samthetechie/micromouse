#include "MazeManipulation.h"
#include "adc.h"
#include "Config.h"
#include "led.h"
#include "initPorts.h"

extern unsigned int Maze [MAZEY][MAZEX];
extern unsigned int Mouse;				//contains heading and xy position of mouse

void AddWall(unsigned char dir, unsigned char x, unsigned char y )
{
     Maze[y][x] |= dir;

     //if (x>0) Maze[y][x-1] |= (dir & NORTH);    		//N
     //if (y<(MAZEY-1)) Maze[y+1][x] |= (dir & EAST );    //E
     //if (x<(MAZEX-1)) Maze[y][x+1] |= (dir & SOUTH);    //S
     //if (y>0) Maze[y-1][x] |= (dir & WEST);    			//W
}

void ClearMaze (void)
{
	unsigned char x = 0;
	unsigned char y = 0;
		//clear out old maze and set all to zero
	while (y < MAZEY)
	{
		while (x < MAZEX)
		{
			Maze[y][x] = 0;
			x++;
		}
		y++;
		x=0;
	}
/*		//	Add outside walls around maze
	for (x=0, y=0; x<MAZEX ; x++)		//Top Walls
	{
		Maze[y][x] |= NORTH;
	}
	for (x=0, y=0; y<MAZEY ; y++)		//Left Walls
	{
		Maze[y][x] |= WEST;
	}
	for (x=(MAZEX-1), y=0; y<MAZEY ; y++)		//Right Walls
	{
		Maze[y][x] |= EAST;
	}
	for (x=0, y=(MAZEX-1); x<MAZEX ; x++)		//Bottom Walls
	{
		Maze[y][x] |= SOUTH;
	}
*/
}

unsigned char GetMouseX( void )
{
	return ( (unsigned char)(Mouse & (0xF)) );
}

unsigned char GetMouseY( void )
{
	return ( (unsigned char)( (Mouse>>4)&(0xF)) );
}

unsigned char GetMouseHeading( void )
{
	return ( (unsigned char)( (Mouse>>8)&(0xF)) );
}

unsigned char GetVisits( unsigned char MouseX, unsigned char MouseY  )
{
	return ( (unsigned char)((Maze[MouseY][MouseX]>>12)&(0xF)) );
}

unsigned char GetWalls( unsigned char MouseX, unsigned char MouseY  )
{
	return ( (unsigned char)((Maze[MouseY][MouseX])&(0xF)) );
}

unsigned char GetExits( unsigned char MouseX, unsigned char MouseY  )
{
	return ( (unsigned char)((~(Maze[MouseY][MouseX]))&(0xF)) );
}


void SetMouseX( unsigned char pos )
{
	Mouse &= 0xFF0;
	Mouse |= (pos & 0xF);
}

void SetMouseY( unsigned char pos )
{
	Mouse &= 0xF0F;
	Mouse |= ((pos & 0xF)<<4);
}

void SetMouseHeading( unsigned char pos )
{
	Mouse &= 0x0FF;
	Mouse |= ((pos & 0xF)<<8);
}
void SetVisits( unsigned char MouseX, unsigned char MouseY ,unsigned char visits )
{
	Maze[MouseY][MouseX] &= 0x0FFF;
	Maze[MouseY][MouseX] |= ((visits & 0xF) << 12);
}

void SetWalls( unsigned char MouseX, unsigned char MouseY ,unsigned char Walls )
{
	Maze[MouseY][MouseX] &= 0xFFF0;
	Maze[MouseY][MouseX] |= (Walls & 0xF);
}



unsigned char ShiftLeftWrapNibble ( unsigned char data)
{
	unsigned char temp=0;
	temp = ((unsigned char)((data & 0xF)));
	temp <<=1;
	temp |= ( (unsigned char)(temp >>4) );
	temp &= (0xF);
	return temp;
}

unsigned char ShiftRightWrapNibble ( unsigned char data)
{
	unsigned char temp=0;
	temp = ((unsigned char)((data & 0xF)<<4));
	temp >>=1;
	temp |= ( (unsigned char)(temp <<4) );
	temp >>=4;
	return temp;
}

unsigned char IsWallLeft()
{

	unsigned char MinDist = 40;
	unsigned char MaxDist = 100;
	unsigned char dist = GetDistLeft();

	if ( (dist >= MinDist) && (dist <= MaxDist ) ) return 1;
	else return 0;
}

unsigned char IsWallRight()
{

	unsigned char MinDist = 40;
	unsigned char MaxDist = 100;
	unsigned char dist = GetDistRight();

	if ( (dist >= MinDist) && (dist <= MaxDist ) ) return 1;
	else return 0;
}

unsigned char IsWallFront()
{

	unsigned char MinDist = 40;
	unsigned char MaxDist = 80;
	unsigned char dist = GetDistFront();

	if ( (dist >= MinDist) && (dist <= MaxDist ) ) return 1;
	else return 0;
}

unsigned char IsWallBack()
{

	/*unsigned char MinDist = 40;
	unsigned char MaxDist = 70;
	unsigned char dist = GetDistBack();

	if ( (dist >= MinDist) && (dist <= MaxDist ) ) return 1;
	else */return 0;
}


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
void SetCurrentCellReserved(void)
{
	unsigned int number = (MOUSENUMBER << 8);	//move mousenumber to correct position
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();

	number &= 0x0F00;	// make sure that mousenumber does not affect any other bits
	Maze[MouseY][MouseX] &= 0xF0FF;	// clear mousenumber bits
	Maze[MouseY][MouseX] |= number;
}


void SetCellUnreserved(unsigned char x, unsigned char y)
{
	Maze[y][x] &= 0xF0FF; // clear bits
}
void SetCurrentCellUnreserved( void )
{
	Maze[GetMouseY()][GetMouseX()] &= 0xF0FF; // clear bits
}
unsigned char GetCellMappedBy(unsigned char x, unsigned char y)
{
	unsigned char temp = (Maze[y][x] >> 4);
	temp &= 0x0f;
	return temp;
}
void SetCellMappedByThisMouse(unsigned char x, unsigned char y)
{
	unsigned int number = (MOUSENUMBER << 4);	//move mousenumber to correct position
	number &= 0x00F0;	// make sure that mousenumber does not affect any other bits
	Maze[y][x] &= 0xFF0F;	// clear mousenumber bits
	Maze[y][x] |= number;

}

void SetThisCellMappedByThisMouse(void)
{
	unsigned int number = (MOUSENUMBER << 4);	//move mousenumber to correct position
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();

	number &= 0x00F0;	// make sure that mousenumber does not affect any other bits
	Maze[MouseY][MouseX] &= 0xFF0F;	// clear mousenumber bits
	Maze[MouseY][MouseX] |= number;

}

