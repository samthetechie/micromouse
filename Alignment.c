#include "Alignment.h"
#include "MazeManipulation.h"
#include "Config.h"
#include "adc.h"
#include "Motor2.h"

static unsigned char LargeErrors = 0;
static unsigned char SmallErrors = 0;

unsigned char DoLRAlignmentForwards (void)
{
	unsigned char WallsRelative = GetWallsRelativeHere();
	//Max Dist = 85, Min Dist = 25
	// 70 = acceptable max, 40 = acceptable min

	unsigned char count = 0;

	if(WallsRelative & LEFT)	//(IsWallLeft())
	{
		unsigned char dist = GetDistLeft();

		if ( dist > 70 )
		{
			DriveTurnLeftForwardsHalf(1);
			DriveNudgeLeftHalf(1);
			count=1;
			IncrementLargeErrors();
		}
		if ( (dist <= 70) && (dist > 60) )
		{
			DriveTurnLeftForwardsHalf(2);
			count=1;
			IncrementSmallErrors();
		}
		if ( (dist <= 60) && (dist > 50) )
		{
		}
		if ( (dist <= 50) && (dist > 40) )
		{
			DriveTurnRightForwardsHalf(2);
			count=1;
			IncrementSmallErrors();
		}
		if ( dist <= 40 )
		{
			DriveTurnRightForwardsHalf(1);
			DriveNudgeRightHalf(1);
			count=1;
			IncrementLargeErrors();
		}
	}
	else if(WallsRelative & RIGHT)	 //(IsWallRight())
	{
		unsigned char dist = GetDistRight();

		if ( dist > 70 )
		{
			DriveTurnRightForwardsHalf(1);
			DriveNudgeRightHalf(1);
			count=1;
			IncrementLargeErrors();
		}
		if ( (dist <= 70) && (dist > 60) )
		{
			DriveTurnRightForwardsHalf(2);
			count=1;
			IncrementSmallErrors();
		}
		if ( (dist <= 60) && (dist > 50) )
		{
		}
		if ( (dist <= 50) && (dist > 40) )
		{
			DriveTurnLeftForwardsHalf(2);
			count=1;
			IncrementSmallErrors();
		}
		if ( dist <= 40 )
		{
			DriveTurnLeftForwardsHalf(1);
			DriveNudgeLeftHalf(1);
			count=1;
			IncrementLargeErrors();
		}
	}
	return count;
}


unsigned char GetWallsRelativeHere (void)
{
	unsigned char MouseX = GetMouseX();
	unsigned char MouseY = GetMouseY();
	unsigned char MouseHeading = GetMouseHeading();
	unsigned char Walls = GetWalls (MouseX, MouseY);

	if (MouseHeading == NORTH);
	if (MouseHeading == EAST)
	{
		Walls = ShiftRightWrapNibble (Walls);
	}
	if (MouseHeading == SOUTH)
	{
		Walls = ShiftRightWrapNibble (ShiftRightWrapNibble (Walls));
	}
	if (MouseHeading == WEST)
	{
		Walls = ShiftLeftWrapNibble (Walls);
	}



	return Walls;
}

unsigned char GetWallsRelative (unsigned char MouseX, unsigned char MouseY)
{
	unsigned char MouseHeading = GetMouseHeading();
	unsigned char Walls = GetWalls (MouseX, MouseY);

	if (MouseHeading == NORTH);
	if (MouseHeading == EAST)
	{
		Walls = ShiftRightWrapNibble (Walls);
	}
	if (MouseHeading == SOUTH)
	{
		Walls = ShiftRightWrapNibble (ShiftRightWrapNibble (Walls));
	}
	if (MouseHeading == WEST)
	{
		Walls = ShiftLeftWrapNibble (Walls);
	}



	return Walls;
}



void DoFBAlignment ( void )
{
/*	if (IsWallFront())//WallsRelative & FRONT);
	{
		DriveBackwardsHalf(4);
		unsigned char dist = GetDistFront();

		if (dist > 40)
		{
			while ( (dist = GetDistFront()) > 40)
			DriveForwards(1);
		}
		DriveForwards(3);
	}

*/

}



void SetLargeErrors (unsigned char errors)
{
	LargeErrors = errors;
}
void IncrementLargeErrors (void )
{
	LargeErrors++;
}
unsigned char GetLargeErrors (void)
{
	return LargeErrors;
}

void SetSmallErrors (unsigned char errors)
{
	SmallErrors = errors;
}
void IncrementSmallErrors (void )
{
	SmallErrors++;
}
unsigned char GetSmallErrors (void)
{
	return SmallErrors;
}


