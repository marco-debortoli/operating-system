/*

	Defines the interface for certain IDT handlers
	Base Class: arch/i386/isr.c

*/

#ifndef _KERNEL_DESCRIPTOR_H
#define _KERNEL_DESCRIPTOR_H

#include <stddef.h>
#include <stdint.h>

void register_interrupt_handler(uint8_t n, void *function);

#endif
