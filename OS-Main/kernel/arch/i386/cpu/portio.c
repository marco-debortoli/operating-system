// PORT FUNCTIONS
// inportb and outportb
// Header file is portio.h

#include <kernel/portio.h>

unsigned char inportb ( unsigned short port ) 
{
    unsigned char rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

void outportb ( unsigned short port, unsigned char data )
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}
