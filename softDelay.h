#ifndef _SOFTDELAY_H_
#define _SOFTDELAY_H_

// software delay
// If MCLK is 8Mhz, delays 1uS times value in n

static void inline softDelay(register unsigned int n)
{
    __asm__ __volatile__ (
		"1: \n"
		" dec	%[n] \n"
		" nop \n"
		" nop \n"
		" nop \n"
		" nop \n"
		" nop \n"
		" jne	1b \n"
        : [n] "+r"(n));
}

#endif //_SOFTDELAY_H_
