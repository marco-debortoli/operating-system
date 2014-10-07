/*

	Keyboard Handler IRQ 1

*/

#include <stddef.h>
#include <kernel/descriptor_tables.h>
#include <stdio.h>
#include <kernel/portio.h>

unsigned char kbdus[128] =
{
	0,
	27,
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'=',
	'\b',
	'\t',
	'q',
	'w',
	'e',
	'r',
	't',
	'y',
	'u',
	'i',
	'o',
	'p',
	'[',
	']',
	'\n',
	'0', // Control
	'a',
	's',
	'd',
	'f',
	'g',
	'h',
	'j',
	'k',
	'l',
	';',
	'\'',
	'`',
	0, // Left shift
	'\\',
	'z',
	'x',
	'c',
	'v',
	'b',
	'n',
	'm',
	',',
	'.',
	'/',
	0, // Right shift
	'*',
	0, // Alt
	' ',
	0, // Caps-Lock
	0, // F1
	0, 0, 0, 0, 0, 0, 0, 0,
	0, // F10
	0, // Num Lock
	0, // Scroll Lock
	0, // Home Key
	0, // Up Arrow
	0, // Page up
	'-',
	0, // Left arrow
	0, 
	0, // Right arrow
	'+',
	0, // End Key
	0, // Down arrow
	0, // Page down
	0, // Insert Key
	0, // Delete key
	0, 0, 0, 
	0, // F11
	0, // F12
	0 // All other keys are undefined
};

void keyboard_handler(struct regs *r)
{
	unsigned char scancode;

	scancode = inportb(0x60);

	// Key is just released
	if (scancode & 0x80)
	{
		// Use for shift, control and whatnot
	}
	else
	{
		// Key is just pressed
		printchar(kbdus[scancode]);
	}
}

void keyboard_install()
{
	irq_install_handler(1, keyboard_handler);
}
