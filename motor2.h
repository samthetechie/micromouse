#ifndef MOTOR_INCL
#define	MOTOR_INCL


void MotorsOff( void );
void Motor1Off( void );
void Motor2Off( void );

void DriveForwardsHalf (unsigned long , unsigned char ecc);
void DriveBackwardsHalf (unsigned long );
void DriveTurnRightForwardsHalf (unsigned long);
void DriveTurnLeftForwardsHalf (unsigned long);
void DriveTurnRightBackwardsHalf (unsigned long);
void DriveTurnLeftBackwardsHalf (unsigned long);
void DriveSpotRotateRightHalf (unsigned long steps);
void DriveSpotRotateLeftHalf (unsigned long steps);

void DriveSmoothCornerRight (void);
void DriveSmoothCornerLeft (void);

void DriveNudgeRightFull (unsigned char steps);
void DriveNudgeLeftFull (unsigned char steps);

void DriveNudgeRightHalf (unsigned char steps);
void DriveNudgeLeftHalf (unsigned char steps);


void DriveForwardsFull (unsigned long , unsigned char ecc);
void DriveBackwardsFull (unsigned long );
void DriveTurnRightForwardsFull (unsigned long);
void DriveTurnLeftForwardsFull (unsigned long);
void DriveTurnRightBackwardsFull (unsigned long);
void DriveTurnLeftBackwardsFull (unsigned long);
void DriveSpotRotateRightFull (unsigned long steps);
void DriveSpotRotateLeftFull (unsigned long steps);


#endif
