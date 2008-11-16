#include "Error.h"

void ThrowError (unsigned int error)
{

	switch(error)

	{

		case 0:
			//
			break;

		case 1:
			//SetFloodHere passed value > 0xFFF (12 bits)
			break;
		case 2:
			//SetFlood passed value > 0xFFF (12 bits)
			break;

		case 3:
			//MazeFlooding sets CurrentFloodValue > 0xFFF (12bits)
			break;

		case 4:
			// No exits from MoveFollowFloodedMaze
			break;





		default:
			//Unknown Error
			break;

	}



while(1);

}




