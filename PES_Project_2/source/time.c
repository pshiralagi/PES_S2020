
#include "time.h"
void wait_ms(volatile uint32_t time)
{
	time = time*1000;
	for (time; time!=0; time--)
	{
		__asm("nop"); //No operation
	}
}
