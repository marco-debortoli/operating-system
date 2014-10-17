/*

	High level interrupt service routines and
	interrupt request handlers

*/

#include <stdio.h>
#include <kernel/portio.h>

// Base ISR handler
void isr_handler(struct regs *r)
{
	if (r->int_no < 32)
	{
		printf("Received interrupt %i", (int)r->int_no);

		// Do nothing (don't want to continually trigger error)
		for (;;);
	}
	
}
