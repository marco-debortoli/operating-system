#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/descriptor_tables.h>
#include <kernel/timer.h>
#include <kernel/keyboard.h>

/* Hardware text mode color constants. */

uint16_t VERSION = 0.03;

void kernel_early(void)
{
	terminal_initialize();

	printf("--- PRE-BOOT PROCESS BEGUN ---\n\n");
	printf("Initializing terminal...\n");
	printf("Initializing descriptor tables...\n");

	init_descriptor_tables();
	
	printf("Initializing IRQ...\n");
	irq_install();

	printf("Initializing Timer...\n");
	timer_install();

	printf("Initializing keyboard...\n");
	keyboard_install();

	asm volatile ("sti");
	printf("\n--- PRE-BOOT PROCESS END ---\n\n");
}

void kernel_main()
{
	printf("RatOS: Version 0.03:\n\n");

	//asm volatile("int $0x45");
	
}

