/*

	The Header File for the reboot function
	Base class: arch/i386/reboot.c

*/

#ifndef _KERNEL_REBOOT_H
#define _KERNEL_REBOOT_H

// Keyboard interface IO port
#define KBRD_INTRFC 0x64

// Keyboard interface bits
#define KBRD_BIT_KDATA 0 	// Keyboard data is in buffer (bit 0)
#define KBRD_BIT_UDATA 1	// User data is in buffer (bit 1)

// Keyboard IO Port
#define KBRD_IO 0x60

// Reset CPU command
#define KBRD_RESET 0xFE

#define bit(n) (1<<(n))

#define check_flag(flags, n) ((flags) & bit(n))

void reboot();

#endif 
