#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/timer.h>

void clear_screen_command ( )
{

	uint16_t VGA_HEIGHT = 25;

	for ( uint16_t i = 1; i < VGA_HEIGHT - 1; i++ )
	{
		clear_line(i);
		terminal_reset();
	}
}

void wait_command ( )
{
	timer_wait(5);
}
	
