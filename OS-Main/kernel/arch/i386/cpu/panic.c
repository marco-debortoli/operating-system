// Panic function

#include <stdint.h>
#include <kernel/tty.h>

void PANIC(const char* message)
{

	//char *ascii_art[ ] = {

	//};

	//for (int i = 0; i < 19; i++) terminal_writestring(ascii_art[i]);

	terminal_writestring(message);

	for(;;);
}
