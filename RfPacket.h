#ifndef RFPACKET_INCL
#define RFPACKET_INCL

/*1*/void AssembleMazePacket (unsigned char x, unsigned char y);

/*2*/void AssembleCellReservePacket(unsigned char x, unsigned char y);
/*3*/void AssembleCellReleasePacket(unsigned char x, unsigned char y);

/*5*/void AssembleStartSynchronisedTimersPacket(unsigned char x, unsigned char y, unsigned char reply);
/*6*/void AssembleCTSPacket(void);
/*7*/void AssembleTestDataPacket(unsigned char data);
/*8*/void AssembleStartTimerPacket(void);

void DisassemblePacket(void);

#endif
