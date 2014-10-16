#include <stdio.h>
 
#if defined(__is_myos_kernel)
#include <kernel/tty.h>
#endif
 
// Prints a character -> calls the terminal write functions
int putchar(int ic)
{
#if defined(__is_myos_kernel)
	char c = (char) ic;
	terminal_write(&c, sizeof(c));
#else
	// TODO: You need to implement a write system call.
#endif
	return ic;
}
