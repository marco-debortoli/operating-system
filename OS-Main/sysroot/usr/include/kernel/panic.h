/*

	The Header File for the global panic function
	Base class: arch/i386/cpu/panic.c

*/

#ifndef _KERNEL_PANIC_H
#define _KERNEL_PANIC_H

#define ASSERT(b) ((b) ? (void)0 : PANIC("ASSERT FAILED"))

void PANIC(const char* message);

#endif
