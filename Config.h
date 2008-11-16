//Contains main configuration: maze dimensions, maximum visit number, robot ID number
#ifndef CONFIG_INCL
#define CONFIG_INCL

#define MAZEX 4
#define MAZEY 4
#define MAXVISITS 15

#define NORTH	(1)
#define EAST	(1<<1)
#define SOUTH	(1<<2)
#define WEST	(1<<3)

#define FRONT	(1)
#define RIGHT	(1<<1)
#define BACK	(1<<2)
#define LEFT	(1<<3)


#define DEGREES360 	(63)
#define DEGREES180 	(31)
#define DEGREES90 	(16)
#define CELL (41)
#define ONEROTATION (50)
#define TWOTHIRDSCELL (34)		// 2/3
#define HALFCELL (26)
#define THIRDSCELL (17)			//1/3

#define TARGETX (3)
#define TARGETY (3)

#define MOUSENUMBER (1)

//#define MOTORFULL
//#define MOTORHALF

#endif

