#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <kernel/reboot.h>
#include <kernel/portio.h>
#include <kernel/descriptor_tables.h>

void reboot()
{
	uint8_t temp;

	asm volatile ("cli");

	printf("Clearing Keyboard data\n");

	do
	{
		// Empty user data from keyboard
		temp = inportb(KBRD_INTRFC);
		if ( check_flag(temp, KBRD_BIT_KDATA) != 0)
			inportb(KBRD_IO);
		
	} while ( check_flag(temp, KBRD_BIT_UDATA != 0) );

	printf("Uninstalling keyboard driver\n");
	irq_uninstall_handler(1);

	printf("Uninstalling timer driver\n");
	irq_uninstall_handler(0);

	outportb(KBRD_INTRFC, KBRD_RESET); // Pulse the CPU reset line

	loop:
		asm volatile ("hlt"); // Backup plan
	goto loop; 
}
