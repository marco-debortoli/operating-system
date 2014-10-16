/*

	A basic shell implementation
	Base Class: arch/i386/shell.c

*/

#include <stddef.h>

#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H

#define MAX_COMMANDS 100

typedef struct
{
	char *name;
	char *description;
	void *function;
} command_table_t;

void shell();
void init_shell();

#endif


