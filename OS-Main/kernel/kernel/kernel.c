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

	// --- Initialize the terminal --- //
	terminal_initialize();
	if ( DEBUG )
	{
		printf("--- PRE-BOOT PROCESS BEGUN ---\n\n");
		printf("Initializing terminal...\n");
		printf("Initializing descriptor tables...\n");
	}

	// --- Initialize the Descriptor Tables --- //
	init_descriptor_tables();
	
	// --- Initialize the IRQ Handlers --- //
	if ( DEBUG ) printf("Initializing IRQ...\n");
	irq_install();

	// --- Install the Timer --- //
	if ( DEBUG ) printf("Initializing Timer...\n");
	timer_install();

	// --- Install the Keyboard Driver --- //
	if ( DEBUG ) printf("Initializing keyboard...\n");
	keyboard_install();

	asm volatile ("sti");


	// --- Initialize the Shell --- //
	init_shell();

	if ( DEBUG ) printf("\n--- PRE-BOOT PROCESS END ---\n\n");
}

// Main kernel function
void kernel_main()
{
	terminal_setup();

	// Call the shell (eventually it will have exit status)
	while ( 1 )
	{
		shell();
	}
	
}

