#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <kernel/tty.h>
#include <kernel/descriptor_tables.h>
#include <kernel/timer.h>
#include <kernel/keyboard.h>

/* Hardware text mode color constants. */

uint16_t VERSION = 0.03;
bool DEBUG = false;

void kernel_early(void)
{
	terminal_initialize();
	if ( DEBUG )
	{
		printf("--- PRE-BOOT PROCESS BEGUN ---\n\n");
		printf("Initializing terminal...\n");
		printf("Initializing descriptor tables...\n");
	}

	init_descriptor_tables();
	
	if ( DEBUG ) printf("Initializing IRQ...\n");
	irq_install();

	if ( DEBUG ) printf("Initializing Timer...\n");
	timer_install();

	if ( DEBUG ) printf("Initializing keyboard...\n");
	keyboard_install();

	asm volatile ("sti");
	if ( DEBUG ) printf("\n--- PRE-BOOT PROCESS END ---\n\n");
}

void kernel_main()
{
	terminal_setup();
	
	//asm volatile("int $0x45");
	
}

