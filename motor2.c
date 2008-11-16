#include "initPorts.h"
#include "Motor2.h"
#include "softDelay.h"
#include "MazeManipulation.h"
#include "Config.h"
#include "Alignment.h"

static void BothFullStepForward ( unsigned char step, unsigned int speed,  unsigned char ecc);
static void BothFullStepBackward ( unsigned char step, unsigned int speed);
static void SpotRotateFullStepRight ( unsigned char step, unsigned int speed);
static void SpotRotateFullStepLeft ( unsigned char step, unsigned int speed);
static void LeftFullStepForward ( unsigned char, unsigned int );
static void LeftFullStepBackward( unsigned char, unsigned int );
static void RightFullStepForward ( unsigned char, unsigned int );
static void RightFullStepBackward( unsigned char, unsigned int );

static void BothHalfStepForward ( unsigned char step, unsigned int speed,  unsigned char ecc);
static void BothHalfStepBackward ( unsigned char step, unsigned int speed);
static void SpotRotateHalfStepRight ( unsigned char step, unsigned int speed);
static void SpotRotateHalfStepLeft ( unsigned char step, unsigned int speed);
static void LeftHalfStepForward  ( unsigned char, unsigned int );
static void LeftHalfStepBackward ( unsigned char, unsigned int );
static void RightHalfStepForward ( unsigned char, unsigned int );
static void RightHalfStepBackward ( unsigned char, unsigned int );

static unsigned int OnTime = 7000;//10000
static unsigned int OffTime = 1;//1000

void MotorsOff (void)
{
	M1P1OFF;
	M1P2OFF;
	M1P3OFF;
	M1P4OFF;

	M2P1OFF;
	M2P2OFF;
	M2P3OFF;
	M2P4OFF;
}

void Motor1Off (void)
{
	M1P1OFF;
	M1P2OFF;
	M1P3OFF;
	M1P4OFF;
}

void Motor2Off (void)
{
	M2P1OFF;
	M2P2OFF;
	M2P3OFF;
	M2P4OFF;
}





// = = = = = = = = = = = = = = = = =HALF STEPS = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


static void BothHalfStepForward ( unsigned char step, unsigned int speed, unsigned char ecc)
{
	unsigned int count = 0;

	while (count < step)
	{

		M1P1ON;		M2P1ON;
		M1P2ON;		M2P2ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P2ON;

		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P2ON;
		M1P3ON;		M2P3ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P3ON;

		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P3ON;
		M1P4ON;		M2P4ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P4ON;		M2P4ON;

		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P4ON;		M2P4ON;
		M1P1ON;		M2P1ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P1ON;		M2P1ON;

		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		if (ecc) count += ( DoLRAlignmentForwards() );

		count++;
	}
}


static void BothHalfStepBackward ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	while (count < step)
	{
		M1P1ON;		M2P1ON;

		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P4ON;		M2P4ON;
		M1P1ON;		M2P1ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P4ON;		M2P4ON;

		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P3ON;
		M1P4ON;		M2P4ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P3ON;

		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P2ON;
		M1P3ON;		M2P3ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P2ON;

		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P1ON;		M2P1ON;
		M1P2ON;		M2P2ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		count++;
	}
}


// = = = = = = = = = = = = = = = = =TURNS = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


static void SpotRotateHalfStepRight ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	while (count < step)
	{
		M1P1ON;		M2P1ON;
		M1P2ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P4ON;
					M2P1ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P4ON;
		M1P3ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P3ON;
					M2P4ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P3ON;
		M1P4ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P4ON;		M2P2ON;
					M2P3ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P4ON;		M2P2ON;
		M1P1ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P1ON;		M2P1ON;
					M2P2ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		count++;
	}
}


static void SpotRotateHalfStepLeft ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	while (count < step)
	{
		M1P1ON;		M2P1ON;
					M2P2ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P4ON;		M2P2ON;
		M1P1ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P4ON;		M2P2ON;
					M2P3ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P3ON;
		M1P4ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P3ON;
					M2P4ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P4ON;
		M1P3ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P4ON;
					M2P1ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P1ON;		M2P1ON;
		M1P2ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		count++;
	}
}


static void LeftHalfStepForward ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	M1P1ON;
	M1P2ON;

	while (count < step)
		{


			M2P1ON;
			M2P2ON;
			softDelay(OnTime);
			Motor2Off();
			softDelay(speed);

			M2P2ON;
			softDelay(OnTime);
			Motor2Off();
			softDelay(speed);


			M2P2ON;
			M2P3ON;
			softDelay(OnTime);
			Motor2Off();
			softDelay(speed);

			M2P3ON;
			softDelay(OnTime);
			Motor2Off();
			softDelay(speed);


			M2P3ON;
			M2P4ON;
			softDelay(OnTime);
			Motor2Off();
			softDelay(speed);

			M2P4ON;
			softDelay(OnTime);
			Motor2Off();
			softDelay(speed);


			M2P4ON;
			M2P1ON;
			softDelay(OnTime);
			Motor2Off();
			softDelay(speed);

			M2P1ON;
			softDelay(OnTime);
			Motor2Off();
			softDelay(speed);

			count++;
	}
	MotorsOff();
}


static void RightHalfStepForward ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	M2P1ON;
	M2P2ON;

	while (count < step)
	{
		M1P1ON;
		M1P2ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P2ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);


		M1P2ON;
		M1P3ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P3ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);


		M1P3ON;
		M1P4ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P4ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);


		M1P4ON;
		M1P1ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P1ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		count++;
	}
	MotorsOff();
}


static void LeftHalfStepBackward ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	M1P1ON;
	M1P2ON;

	while (count < step)
	{
		M2P1ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P4ON;
		M2P1ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P4ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P3ON;
		M2P4ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P3ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P2ON;
		M2P3ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P2ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P1ON;
		M2P2ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		count++;
	}
	MotorsOff();
}


static void RightHalfStepBackward ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	M2P1ON;
	M2P2ON;

	while (count < step)
		{
		M1P1ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P4ON;
		M1P1ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P4ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P3ON;
		M1P4ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P3ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P2ON;
		M1P3ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P2ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P1ON;
		M1P2ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		count++;
	}
	MotorsOff();
}

// = = = = = = = = = = = = = = = = =FULL STEPS = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

static void BothFullStepForward ( unsigned char step, unsigned int speed, unsigned char ecc)
{
	unsigned int count = 0;

	while (count < step)
	{

		M1P1ON;		M2P1ON;
		M1P2ON;		M2P2ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P2ON;
		M1P3ON;		M2P3ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P3ON;
		M1P4ON;		M2P4ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);


		M1P4ON;		M2P4ON;
		M1P1ON;		M2P1ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		if (ecc) count += ( DoLRAlignmentForwards() );

		count++;
	}
}


static void BothFullStepBackward ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	while (count < step)
	{

		M1P4ON;		M2P4ON;
		M1P1ON;		M2P1ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P3ON;
		M1P4ON;		M2P4ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P2ON;
		M1P3ON;		M2P3ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P1ON;		M2P1ON;
		M1P2ON;		M2P2ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		count++;
	}
}


// = = = = = = = = = = = = = = = = =TURNS = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


static void SpotRotateFullStepRight ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	while (count < step)
	{
		M1P1ON;		M2P4ON;
		M1P2ON;		M2P1ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);


		M1P2ON;		M2P3ON;
		M1P3ON;		M2P4ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P2ON;
		M1P4ON;		M2P3ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P4ON;		M2P1ON;
		M1P1ON;		M2P2ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		count++;
	}
}


static void SpotRotateFullStepLeft ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	while (count < step)
	{
		M1P4ON;		M2P1ON;
		M1P1ON;		M2P2ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P3ON;		M2P2ON;
		M1P4ON;		M2P3ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P2ON;		M2P3ON;
		M1P3ON;		M2P4ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		M1P1ON;		M2P4ON;
		M1P2ON;		M2P1ON;
		softDelay(OnTime);
		MotorsOff();
		softDelay(speed);

		count++;
	}
}


static void LeftFullStepForward ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	M1P1ON;
	M1P2ON;

	while (count < step)
	{
		M2P1ON;
		M2P2ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P2ON;
		M2P3ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P3ON;
		M2P4ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P4ON;
		M2P1ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		count++;
	}
	MotorsOff();
}


static void RightFullStepForward ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	M2P1ON;
	M2P2ON;

	softDelay(OnTime);

	while (count < step)
	{
		M1P1ON;
		M1P2ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P2ON;
		M1P3ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P3ON;
		M1P4ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P4ON;
		M1P1ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		count++;
	}
	softDelay(OnTime);
	MotorsOff();
}


static void LeftFullStepBackward ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	M1P1ON;
	M1P2ON;

	while (count < step)
	{
		M2P4ON;
		M2P1ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P3ON;
		M2P4ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P2ON;
		M2P3ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		M2P1ON;
		M2P2ON;
		softDelay(OnTime);
		Motor2Off();
		softDelay(speed);

		count++;
	}
	MotorsOff();
}


static void RightFullStepBackward ( unsigned char step, unsigned int speed)
{
	unsigned int count = 0;

	M2P1ON;
	M2P2ON;

	while (count < step)
	{
		M1P4ON;
		M1P1ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P3ON;
		M1P4ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P2ON;
		M1P3ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		M1P1ON;
		M1P2ON;
		softDelay(OnTime);
		Motor1Off();
		softDelay(speed);

		count++;
	}
	MotorsOff();
}

// = = = = = = = = = = = = = = = = =EXTERNAL DRIVE FUNCTIONS= HALF STEP = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void DriveForwardsHalf (unsigned long steps, unsigned char ecc)
{
	BothHalfStepForward(steps, OffTime, ecc);
}

void DriveBackwardsHalf (unsigned long steps)
{
	BothHalfStepBackward(steps, OffTime);
}

void DriveTurnRightForwardsHalf (unsigned long steps)
{
	RightHalfStepForward(steps, OffTime);
}

void DriveTurnLeftForwardsHalf (unsigned long steps)
{
	LeftHalfStepForward(steps, OffTime);
}

void DriveTurnRightBackwardsHalf (unsigned long steps)
{
	RightHalfStepBackward(steps, OffTime);
}

void DriveTurnLeftBackwardsHalf (unsigned long steps)
{
	RightHalfStepBackward(steps, OffTime);
}

void DriveSpotRotateRightHalf (unsigned long steps)
{
	SpotRotateHalfStepRight(steps, OffTime);
}

void DriveSpotRotateLeftHalf (unsigned long steps)
{
	SpotRotateHalfStepLeft(steps, OffTime);
}

// = = = = = = = = = = = = = = = = = SMOOTH CORNERS= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

void DriveSmoothCornerRight (void)
{}

void DriveSmoothCornerLeft (void)
{}


//= = = = = = = = = = = = = = = = NUDGES LEFT AND RIGHT = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

void DriveNudgeLeftFull (unsigned char steps)
{
	unsigned char LocalCount=0;

	while ( LocalCount < steps)
	{
		LeftFullStepForward		(8, OffTime);
		RightFullStepForward	(8, OffTime);
		LeftFullStepBackward	(8, OffTime);
		RightFullStepBackward	(8, OffTime);
		LocalCount++;
	}
}

void DriveNudgeRightFull (unsigned char steps)
{
	unsigned char LocalCount=0;

	while ( LocalCount < steps)
	{
		RightFullStepForward	(8, OffTime);
		LeftFullStepForward		(8, OffTime);
		RightFullStepBackward	(8, OffTime);
		LeftFullStepBackward	(8, OffTime);
		LocalCount++;
	}
}

void DriveNudgeLeftHalf (unsigned char steps)
{
	unsigned char LocalCount=0;

	while ( LocalCount < steps)
	{
		LeftHalfStepForward		(3, OffTime);
		RightHalfStepForward	(3, OffTime);
		LeftHalfStepBackward	(3, OffTime);
		RightHalfStepBackward	(3, OffTime);
		LocalCount++;
	}
}

void DriveNudgeRightHalf (unsigned char steps)
{
	unsigned char LocalCount=0;

	while ( LocalCount < steps)
	{
		RightHalfStepForward	(3, OffTime);
		LeftHalfStepForward		(3, OffTime);
		RightHalfStepBackward	(3, OffTime);
		LeftHalfStepBackward	(3, OffTime);
		LocalCount++;
	}
}



// = = = = = = = = = = = = = = = = =EXTERNAL DRIVE FUNCTIONS= Full STEP = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void DriveForwardsFull (unsigned long steps, unsigned char ecc)
{
	BothFullStepForward(steps, OffTime, ecc);
}

void DriveBackwardsFull (unsigned long steps)
{
	BothFullStepBackward(steps, OffTime);
}

void DriveTurnRightForwardsFull (unsigned long steps)
{
	RightFullStepForward(steps, OffTime);
}

void DriveTurnLeftForwardsFull (unsigned long steps)
{
	LeftFullStepForward(steps, OffTime);
}

void DriveTurnRightBackwardsFull (unsigned long steps)
{
	RightFullStepBackward(steps, OffTime);
}

void DriveTurnLeftBackwardsFull (unsigned long steps)
{
	RightFullStepBackward(steps, OffTime);
}

void DriveSpotRotateRightFull (unsigned long steps)
{
	SpotRotateFullStepRight(steps, OffTime);
}

void DriveSpotRotateLeftFull (unsigned long steps)
{
	SpotRotateFullStepLeft(steps, OffTime);
}



