#ifndef ALIGNMENT_INCL
#define ALIGNMENT_INCL








unsigned char DoLRAlignmentForwards (void);
unsigned char GetWallsRelativeHere (void);
unsigned char GetWallsRelative (unsigned char, unsigned char);
void DoFBAlignment ( void );



void SetLargeErrors (unsigned char errors);
void IncrementLargeErrors (void );
unsigned char GetLargeErrors (void);


void SetSmallErrors (unsigned char errors);
void IncrementSmallErrors (void );
unsigned char GetSmallErrors (void);







#endif
