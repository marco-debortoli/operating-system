/*

	High level interrupt service routines and
	interrupt request handlers

*/

#include <stdio.h>
#include <kernel/portio.h>

void* interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, void *function)
{
	interrupt_handlers[n] = function;
}

// Base ISR handler
void isr_handler(struct regs *r)
{
	
	if (interrupt_handlers[r->int_no] != 0)
	{
		void (*command_function)(struct regs *r) = interrupt_handlers[(int)r->int_no];
        	command_function(r);
    	}
    	else
    	{
		printf("Received interrupt %i", (int)r->int_no);

		// Do nothing (don't want to continually trigger error)
		for (;;);
    	}


}
