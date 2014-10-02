#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <kernel/vga.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void clear_line(uint16_t line)
{
	for (size_t x = 0; x < VGA_WIDTH; x++)
	{
		const size_t index = line * VGA_WIDTH + x;
		terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	}
}

void outb(unsigned short port, unsigned char value)
{
	asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
}

void move_cursor(int row, int col)
{
	unsigned short location = (row*80) + col;

	outb(0x3D4, 0x0F); 
	outb(0x3D5, (char)(location&0xFF));

	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char)((location >> 8)&0xFF));
}	

void terminal_scroll()
{

	// Move all other lines up
	for (size_t y = 1; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index1 = y * VGA_WIDTH + x;
			const size_t index2 = (y-1) * VGA_WIDTH + x;
			terminal_buffer[index2] = terminal_buffer[index1];
		}
	}

	// Clear last line
	clear_line(VGA_HEIGHT - 1);

	terminal_row = VGA_HEIGHT - 1;

}

void terminal_putchar(char c)
{

	if ( c == '\n' )
	{
		terminal_column = 0;
		terminal_row++ ;
		if ( terminal_row == VGA_HEIGHT) 
		{
			terminal_scroll();
		}
		
		move_cursor(terminal_row, terminal_column);
		
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column == VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row == VGA_HEIGHT )
		{
			terminal_scroll();
		}
	}

	move_cursor(terminal_row, terminal_column);
}

void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);

}

void terminal_write(const char* data, size_t size)
{
	for ( size_t i = 0; i < size; i++ )
		terminal_putchar(data[i]);
}
