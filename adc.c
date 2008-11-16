//ADC control: returns distance in millimetres using AdcLut.c
#include <io.h>
#include <signal.h>
#include "adc.h"
#include "led.h"

extern const unsigned char adcTable[];

void AdcInit(void)
{
/*	ADC12CTL0 = 0;
	ADC12CTL1 = 0;

	ADC12CTL0 = SHT1_4 | SHT0_12 | MSC | REF2_5V | REFON | ADC12ON;

	// start with mem 0, software start
	// clock divider 1, adc12 clock
	ADC12CTL1 = CSTARTADD_0 | SHS_0 | SHP | ADC12DIV_0 | ADC12SSEL_0 | CONSEQ_1 ;

	// set up conversion memory control register
	// read channels 0-3 using AVcc & AVss
	ADC12MCTL0 = SREF_1 | INCH_A0;
	ADC12MCTL1 = SREF_1 | INCH_A1;
	ADC12MCTL2 = SREF_1 | INCH_A2;
	ADC12MCTL3 = SREF_1 | INCH_A3;
	ADC12MCTL4 = EOS | SREF_1 | INCH_A4;

	ADC12CTL0 |= ENC;	// enable conversions

	*/
}

void AdcStart(void)
{
	ADC12CTL0 |= ADC12SC;	// start adc
}

unsigned int GetIRLeft(void)
{
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12IFG &= ~(1);

	ADC12CTL0 = SHT1_4 | SHT0_12 | REF2_5V | REFON | ADC12ON;

	// start with mem 0, software start
	// clock divider 1, adc12 clock
	ADC12CTL1 = CSTARTADD_1 | SHS_0 | SHP | ADC12DIV_0 | ADC12SSEL_0 | CONSEQ_0 ;

	// set up conversion memory control register
	// read channels 0-3 using AVcc & AVss

	ADC12MCTL1 = EOS | SREF_1 | INCH_A2;	//physical channel 2

	ADC12CTL0 |= ENC;	// enable conversions
	ADC12CTL0 |= ADC12SC;	// start adc

	while ( (ADC12CTL1 & ADC12BUSY) );	//while busy

	while ( ! (ADC12IFG & (1<<1)))	// while (NOT [conversion complete flag MEM0] )
	{

	}

	return ADC12MEM1;

}

unsigned int GetIRRight(void)
{
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12IFG &= ~(1);

	ADC12CTL0 = SHT1_4 | SHT0_12 | REF2_5V | REFON | ADC12ON;

	// start with mem 0, software start
	// clock divider 1, adc12 clock
	ADC12CTL1 = CSTARTADD_1 | SHS_0 | SHP | ADC12DIV_0 | ADC12SSEL_0 | CONSEQ_0 ;

	// set up conversion memory control register
	// read channels 0-3 using AVcc & AVss

	ADC12MCTL1 = EOS | SREF_1 | INCH_A3;	//physical channel 3

	ADC12CTL0 |= ENC;	// enable conversions
	ADC12CTL0 |= ADC12SC;	// start adc

	while ( (ADC12CTL1 & ADC12BUSY) );	//while busy

	while ( ! (ADC12IFG & (1<<1)))	// while (NOT [conversion complete flag MEM0] )
	{

	}

	return ADC12MEM1;;
}

unsigned int GetIRFront(void)
{
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12IFG &= ~(1);

	ADC12CTL0 = SHT1_4 | SHT0_12 | REF2_5V | REFON | ADC12ON;

	// start with mem 0, software start
	// clock divider 1, adc12 clock
	ADC12CTL1 = CSTARTADD_1 | SHS_0 | SHP | ADC12DIV_0 | ADC12SSEL_0 | CONSEQ_0 ;

	// set up conversion memory control register
	// read channels 0-3 using AVcc & AVss

	ADC12MCTL1 = EOS | SREF_1 | INCH_A1;	//physical channel 0

	ADC12CTL0 |= ENC;	// enable conversions
	ADC12CTL0 |= ADC12SC;	// start adc

	while ( (ADC12CTL1 & ADC12BUSY) );	//while busy

	while ( ! (ADC12IFG & (1<<1)))	// while (NOT [conversion complete flag MEM0] )
	{

	}

	return ADC12MEM1;
}


unsigned char GetDistLeft (void)
{
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12IFG &= ~(1);

	ADC12CTL0 = SHT1_4 | SHT0_12 | REF2_5V | REFON | ADC12ON;

	// start with mem 0, software start
	// clock divider 1, adc12 clock
	ADC12CTL1 = CSTARTADD_1 | SHS_0 | SHP | ADC12DIV_0 | ADC12SSEL_0 | CONSEQ_0 ;

	// set up conversion memory control register
	// read channels 0-3 using AVcc & AVss

	ADC12MCTL1 = EOS | SREF_1 | INCH_A2;

	ADC12CTL0 |= ENC;	// enable conversions
	ADC12CTL0 |= ADC12SC;	// start adc

	while ( (ADC12CTL1 & ADC12BUSY) );	//while busy

	while ( ! (ADC12IFG & (1<<1)))	// while (NOT [conversion complete flag MEM0] )
	{
//LED16TOGGLE;
	}
//LED16OFF;


	return adcTable[ ((unsigned char)(ADC12MEM1>>4)) ];
}

unsigned char GetDistRight (void)
{
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12IFG &= ~(1);

	ADC12CTL0 = SHT1_4 | SHT0_12 | REF2_5V | REFON | ADC12ON;

	// start with mem 0, software start
	// clock divider 1, adc12 clock
	ADC12CTL1 = CSTARTADD_1 | SHS_0 | SHP | ADC12DIV_0 | ADC12SSEL_0 | CONSEQ_0 ;

	// set up conversion memory control register
	// read channels 0-3 using AVcc & AVss

	ADC12MCTL1 = EOS | SREF_1 | INCH_A3;

	ADC12CTL0 |= ENC;	// enable conversions
	ADC12CTL0 |= ADC12SC;	// start adc

	while ( (ADC12CTL1 & ADC12BUSY) );	//while busy

	while ( ! (ADC12IFG & (1<<1)))	// while (NOT [conversion complete flag MEM0] )
	{
//LED16TOGGLE;
	}
//LED16OFF;


	return adcTable[ ((unsigned char)(ADC12MEM1>>4)) ];
}

unsigned char GetDistFront (void)
{
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12IFG &= ~(1);

	ADC12CTL0 = SHT1_4 | SHT0_12 | REF2_5V | REFON | ADC12ON;

	// start with mem 0, software start
	// clock divider 1, adc12 clock
	ADC12CTL1 = CSTARTADD_1 | SHS_0 | SHP | ADC12DIV_0 | ADC12SSEL_0 | CONSEQ_0 ;

	// set up conversion memory control register
	// read channels 0-3 using AVcc & AVss

	ADC12MCTL1 = EOS | SREF_1 | INCH_A1;

	ADC12CTL0 |= ENC;	// enable conversions
	ADC12CTL0 |= ADC12SC;	// start adc

	while ( (ADC12CTL1 & ADC12BUSY) );	//while busy

	while ( ! (ADC12IFG & (1<<1)))	// while (NOT [conversion complete flag MEM0] )
	{
//LED16TOGGLE;
	}
//LED16OFF;


	return adcTable[ ((unsigned char)(ADC12MEM1>>4)) ];
}

unsigned char GetDistBack (void)
{
	ADC12CTL0 = 0;
	ADC12CTL1 = 0;
	ADC12IFG &= ~(1);

	ADC12CTL0 = SHT1_4 | SHT0_12 | REF2_5V | REFON | ADC12ON;

	// start with mem 0, software start
	// clock divider 1, adc12 clock
	ADC12CTL1 = CSTARTADD_1 | SHS_0 | SHP | ADC12DIV_0 | ADC12SSEL_0 | CONSEQ_0 ;

	// set up conversion memory control register
	// read channels 0-3 using AVcc & AVss

	ADC12MCTL1 = EOS | SREF_1 | INCH_A4;

	ADC12CTL0 |= ENC;	// enable conversions
	ADC12CTL0 |= ADC12SC;	// start adc

	while ( (ADC12CTL1 & ADC12BUSY) );	//while busy

	while ( ! (ADC12IFG & (1<<1)))	// while (NOT [conversion complete flag MEM0] )
	{
//LED16TOGGLE;
	}
//LED16OFF;


	return adcTable[ ((unsigned char)(ADC12MEM1>>4)) ];
}



