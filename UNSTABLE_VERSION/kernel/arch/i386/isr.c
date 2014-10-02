/*

	High level interrupt service routines and
	interrupt request handlers

*/

#include <stdio.h>
#include <kernel/isr.h>

void isr_handler(struct regs *r)
{
	if (r->int_no < 32)
	{
		printf("Received interrupt");
		for (;;);
	}
	
}
