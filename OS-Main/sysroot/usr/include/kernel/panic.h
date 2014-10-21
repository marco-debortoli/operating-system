/*

	The Header File for the global panic function
	Base class: arch/i386/cpu/panic.c

*/

#ifndef _KERNEL_PANIC_H
#define _KERNEL_PANIC_H

void PANIC(const char* message);

#endif
