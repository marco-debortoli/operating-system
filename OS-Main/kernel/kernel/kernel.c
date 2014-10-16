#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <kernel/tty.h>
#include <kernel/descriptor_tables.h>
#include <kernel/timer.h>
#include <kernel/keyboard.h>
#include <kernel/shell.h>

/* Hardware text mode color constants. */

bool DEBUG = false;

// Called before the main kernel function
// Initializes all hardware
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

	init_shell();


	if ( DEBUG ) printf("\n--- PRE-BOOT PROCESS END ---\n\n");
}

// Main kernel function
void kernel_main()
{
	terminal_setup();

	while ( 1 )
	{
		shell();
	}
	
}

