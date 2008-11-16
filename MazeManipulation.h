#ifndef MAZEMANIPULATION_INCL
#define MAZEMANIPULATION_INCL






void ClearMaze (void);
void AddWall(unsigned char dir, unsigned char x, unsigned char y );

unsigned char GetMouseY( void );
unsigned char GetMouseX( void );
unsigned char GetMouseHeading( void );
unsigned char GetVisits( unsigned char MouseX, unsigned char MouseY );
unsigned char GetWalls( unsigned char MouseX, unsigned char MouseY );
unsigned char GetExits( unsigned char MouseX, unsigned char MouseY );

void SetMouseX( unsigned char );
void SetMouseY( unsigned char );
void SetMouseHeading( unsigned char );
void SetVisits( unsigned char MouseX, unsigned char MouseY ,unsigned char Visits);
void SetWalls( unsigned char MouseX, unsigned char MouseY ,unsigned char Walls);

unsigned char ShiftLeftWrapNibble ( unsigned char );
unsigned char ShiftRightWrapNibble ( unsigned char );


unsigned char IsWallLeft(void);
unsigned char IsWallRight(void);
unsigned char IsWallFront(void);
unsigned char IsWallBack(void);


unsigned char GetCellReserved(unsigned char x, unsigned char y);
void SetCellReserved(unsigned char x, unsigned char y);
void SetCurrentCellReserved(void);
void SetCellUnreserved(unsigned char x, unsigned char y);
void SetCurrentCellUnreserved( void );

unsigned char GetCellMappedBy(unsigned char x, unsigned char y);
void SetCellMappedByThisMouse(unsigned char x, unsigned char y);

void SetThisCellMappedByThisMouse(void);




#endif
