
#include <timer.h>
void wait_ms(volatile uint32_t time)
{
	time = time*4250;	//Values tested on oscilloscope
	for (time; time!=0; time--)
	{
		__asm("nop"); //No operation
	}
}
