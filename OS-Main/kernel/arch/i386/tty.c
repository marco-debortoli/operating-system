#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <kernel/vga.h>
#include <kernel/portio.h>

size_t terminal_row;
size_t terminal_column;
size_t terminal_session;
uint8_t terminal_color;
uint16_t* terminal_buffer;
char* command;

// Initialize the terminal
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

// A function to set the terminal color (color is made with make_color)
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

// Puts character entry at desired location
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

// Clears a line
void clear_line(uint16_t line)
{
	for (size_t x = 0; x < VGA_WIDTH; x++)
	{
		const size_t index = line * VGA_WIDTH + x;
		terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	}
}

// Moves the cursor
void move_cursor(int row, int col)
{
	unsigned short location = (row*80) + col;

	outportb(0x3D4, 0x0F); 
	outportb(0x3D5, (char)(location&0xFF));

	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (unsigned char)((location >> 8)&0xFF));
}	

// Gets the current row that the cursor is on
size_t terminal_getrow( )
{
	return terminal_row;
}

// Gets the current column that the cursor is on
size_t terminal_getcolumn( )
{
	return terminal_column;
}

void terminal_scroll()
{

	// Move all other lines up
	for (size_t y = 2; y < VGA_HEIGHT; y++)
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

// Creates the > that starts every line
void terminal_startline ( )
{
	terminal_putentryat('>', make_color(COLOR_RED, COLOR_BLACK), terminal_column, terminal_row);
	terminal_column += 2;
	move_cursor(terminal_row, terminal_column);

}

// The main function for putting characters
void terminal_putchar(char c)
{

	// Special characters "\n" "\t" "\b" "\v"

	switch ( c )
	{
		case '\n':
			terminal_column = 0;
			terminal_session = 0;
			terminal_row++;
			if ( terminal_row == VGA_HEIGHT ) terminal_scroll();
			
			move_cursor(terminal_row, terminal_column);
			break;

		case '\t':
			for ( uint32_t i = 0; i < 5; i++ )
			{
				terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
				if ( ++terminal_column == VGA_WIDTH )
				{
					terminal_column = 0;
					if ( ++terminal_row == VGA_HEIGHT ) terminal_scroll();
				}
				terminal_session++;
			}
			move_cursor(terminal_row, terminal_column);
			break;
				
		case '\b':
			if ( terminal_session == 0 )
			{
				// Do nothing (Don't want to be able to backspace more than current command ('>'))
				break;
			}

			if ( terminal_column == 0 )
			{
				terminal_column = VGA_WIDTH - 1;
				terminal_row--;
				terminal_session--;
			}
			else 
			{
				terminal_column--;
				terminal_session--;
			}

			terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
			move_cursor(terminal_row, terminal_column);
			break;	

		default:
			terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
			if ( ++terminal_column == VGA_WIDTH )
			{
				terminal_column = 0;
				if ( ++terminal_row == VGA_HEIGHT ) terminal_scroll();
			}
			terminal_session++;
			move_cursor(terminal_row, terminal_column);
			break;
	}
}

// Writes a string
void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);

}

// Writes data
void terminal_write(const char* data, size_t size)
{
	for ( size_t i = 0; i < size; i++ )
		terminal_putchar(data[i]);
}

// Sets up terminal
void terminal_setup()
{
	// Creates the header at the top of the terminal
	terminal_color = make_color(COLOR_WHITE, COLOR_DARK_GREY);
	terminal_writestring("\tMARCO-OS: Version 0.05");
	for ( size_t i = 0; i < VGA_WIDTH - 27; i++ )
	{
		terminal_putchar(' ');
	}
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
}
