#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/descriptor_tables.h>

/* Hardware text mode color constants. */

uint16_t VERSION = 0.03;

void kernel_early(void)
{
	terminal_initialize();

	printf("--- PRE-BOOT PROCESS BEGUN ---\n\n");
	printf("Initializing terminal...\n");
	printf("Initializing descriptor tables...\n");

	init_descriptor_tables();

	printf("\n--- PRE-BOOT PROCESS END ---\n\n");
}

int kernel_main()
{
	printf("RatOS: Version 0.03:\n");

	//asm volatile("int $0x0");

	return 1/0;
}

