/*

	Header file for the terminal mode writing functions
	Base Class: arch/i386/tty.c

*/

#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_setup();
void terminal_startline();
void terminal_reset();
void terminal_setcolor(uint8_t color);
void clear_line(int);
void move_cursor(int row, int col);

#endif
