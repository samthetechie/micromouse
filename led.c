//Function to output unsigned bytes and unsigned integers to LEDs
#include "led.h"
#include "initPorts.h"

/*void SetLeds (unsigned int led)
{
	LED8OFF;
	LED7OFF;
	LED6OFF;
	LED5OFF;

	LED4OFF;
	LED3OFF;
	LED2OFF;
	LED1OFF;

	LED9OFF;
	LED10OFF;
	LED11OFF;
	LED12OFF;

	LED13OFF;
	LED14OFF;
	LED15OFF;
	LED16OFF;

	if ( (led & (1<<7))>>7 ) LED8ON;
	if ( (led & (1<<6))>>6 ) LED7ON;
	if ( (led & (1<<5))>>5 ) LED6ON;
	if ( (led & (1<<4))>>4 ) LED5ON;

	if ( (led & (1<<3))>>3 ) LED4ON;
	if ( (led & (1<<2))>>2 ) LED3ON;
	if ( (led & (1<<1))>>1 ) LED2ON;
	if ( (led & (1<<0))>>0 ) LED1ON;

	if ( (led & (1<<8))>>8 ) LED9ON;
	if ( (led & (1<<9))>>9 ) LED10ON;
	if ( (led & (1<<10))>>10 ) LED11ON;
	if ( (led & (1<<11))>>11 ) LED12ON;

	if ( (led & (1<<12))>>12 ) LED13ON;
	if ( (led & (1<<13))>>13 ) LED14ON;
	if ( (led & (1<<14))>>14 ) LED15ON;
	if ( (led & (1<<15))>>15 ) LED16ON;
}

void SetLedsUpper (unsigned char led)
{
	LED9OFF;
	LED10OFF;
	LED11OFF;
	LED12OFF;

	LED13OFF;
	LED14OFF;
	LED15OFF;
	LED16OFF;

	if ( (led & (1<<7))>>7 ) LED16ON;
	if ( (led & (1<<6))>>6 ) LED15ON;
	if ( (led & (1<<5))>>5 ) LED14ON;
	if ( (led & (1<<4))>>4 ) LED13ON;

	if ( (led & (1<<3))>>3 ) LED12ON;
	if ( (led & (1<<2))>>2 ) LED11ON;
	if ( (led & (1<<1))>>1 ) LED10ON;
	if ( (led & (1<<0))>>0 ) LED9ON;
}
*/
void SetLedsLower (unsigned char led)
{
	LED8OFF;
	LED7OFF;
	LED6OFF;
	LED5OFF;

	LED4OFF;
	LED3OFF;
	LED2OFF;
	LED1OFF;

	if ( (led & (1<<7))>>7 ) LED8ON;
	if ( (led & (1<<6))>>6 ) LED7ON;
	if ( (led & (1<<5))>>5 ) LED6ON;
	if ( (led & (1<<4))>>4 ) LED5ON;

	if ( (led & (1<<3))>>3 ) LED4ON;
	if ( (led & (1<<2))>>2 ) LED3ON;
	if ( (led & (1<<1))>>1 ) LED2ON;
	if ( (led & (1<<0))>>0 ) LED1ON;
}
