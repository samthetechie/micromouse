#ifndef MAPMAZE_INCL
#define MAPMAZE_INCL

void AnalyseCellFB (void) ;
void AnalyseCellLR (void) ;

void IncrementCell (void);

unsigned char GetExitDir (void);

void MoveToNewCellLogical (unsigned char dir);


void Rotate (unsigned char);
unsigned char IsMazeMapped (void);

void IncrementCellVisits (void);
void IncrementCellCount (void);

void DriveToEndOfCurrentCellCorrecting (void);
void DriveToStartOfNextCellNOTCorrecting (void);
void DriveToMiddleOfNewCellCorrecting (void);

void SetCellCount(unsigned int);
unsigned int GetCellCount(void);

void TxCellInfo (void);

#endif
