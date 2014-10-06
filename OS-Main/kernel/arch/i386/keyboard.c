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
	'0',
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
	0,
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
	0,
	'*',
	0,
	' ',
	0,
	0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0,
	0,
	0,
	0,
	0,
	0,
	'-',
	0,
	0,
	0,
	'+',
	0,
	0,
	0,
	0,
	0,
	0, 0, 0,
	0,
	0,
	0
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
