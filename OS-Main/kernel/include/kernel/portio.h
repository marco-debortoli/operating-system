/*

	Header file for porting I/O
	Base Class: arch/i386/portio.c

*/

#ifndef _KERNEL_PORTIO_H
#define _KERNEL_PORTIO_H

#include <stdint.h>

// This defines what the stack looks like after an ISR was running
struct regs 
{
    uint32_t gs, fs, es, ds;      			// pushed the segs last 
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  	// pushed by 'pusha' 
    uint32_t int_no, err_code;    			// our 'push byte #' and ecodes do this 
    uint32_t eip, cs, eflags, useresp, ss;  		// pushed by the processor automatically
};

unsigned char inportb ( unsigned short port );

void outportb ( unsigned short port, unsigned char data );

#endif
