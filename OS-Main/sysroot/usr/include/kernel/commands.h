/*

	Shell commands
	Base Class: arch/i386/commands.c

*/

#ifndef _KERNEL_COMMANDS_H
#define _KERNEL_COMMANDS_H

#include <stdint.h>

void clear_screen_command();
void wait_command();
void restart_command();
void get_time_command();
void get_date_command();

#endif
