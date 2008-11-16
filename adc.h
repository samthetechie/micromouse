#ifndef ADC_INCL
#define ADC_INCL

//#define IR0 ADC12MEM0	//front
//#define IR1 ADC12MEM1	//back
//#define IR2 ADC12MEM2	//left
//#define IR3 ADC12MEM3	//right

//#define	IRFRONT	IR0
//#define IRBACK	IR1
//#define	IRLEFT	IR2
//#define	IRRIGHT	IR3

#define IR0IFG (ADC12IFG & 1)
#define IR1IFG (ADC12IFG & (1<<1))
#define IR2IFG (ADC12IFG & (1<<2))
#define IR3IFG (ADC12IFG & (1<<3))

void AdcInit(void);
void AdcStart(void);

unsigned int GetIRLeft(void);
unsigned int GetIRRight(void);
unsigned int GetIRFront(void);
//unsigned int GetIRBack(void);

unsigned char GetDistLeft (void);
unsigned char GetDistRight (void);
unsigned char GetDistFront (void);
unsigned char GetDistBack (void);

 #endif
