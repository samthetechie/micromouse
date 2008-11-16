#ifndef CELLRESERVARION_INCL
#define CELLRESERVARION_INCL


unsigned char GetCellReserved(unsigned char x, unsigned char y);
void SetCellReserved(unsigned char x, unsigned char y);
void SetCellReservedByAnotherMouse(unsigned char x, unsigned char y, unsigned char mouse);

void SetCellUnreserved(unsigned char x, unsigned char y);
void SetCurrentCellUnreserved( void );



void ReserveCell(unsigned char x,unsigned char y);
void ReserveCurrentCell(void);
void ReserveCellsAroundHere(void);
unsigned char ReserveCellsAround(unsigned char MoveDir);







void ReleaseCell(unsigned char x,unsigned char y);
void ReleaseCurrentCell(void);
void ReleaseOldCells(unsigned char MoveDir);
void ReleaseWalledCells (void);



#endif
