#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
 
// Abort function
__attribute__((__noreturn__))
void abort(void)
{
	// TODO: Add proper kernel panic.
	printf("Kernel Panic: abort()\n");
	while ( 1 ) { }
	__builtin_unreachable();
}
