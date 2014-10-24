/*

	Keyboard Handler IRQ 1

*/

#include <stddef.h>
#include <kernel/descriptor_tables.h>
#include <stdio.h>
#include <kernel/portio.h>
#include <stdbool.h>
#include <kernel/tty.h>

int LEFT_SHIFT_KEY_RELEASED_SCANCODE = 170;
int LEFT_SHIFT_KEY_PRESSED_SCANCODE = 42;

int RIGHT_SHIFT_KEY_RELEASED_SCANCODE = 182;
int RIGHT_SHIFT_KEY_PRESSED_SCANCODE = 54;

bool SHIFT_KEY_PRESSED = false;

int CAPS_KEY_PRESSED_SCANCODE = 58;
int CAPS_KEY_RELEASED_SCANCODE = 187;
bool CAPS_KEY_PRESSED = false;

int CONTROL_PRESSED_SCANCODE = 29;
int CONTROL_RELEASED_SCANCODE = 157;
bool CONTROL_KEY_PRESSED = false;

int ALT_PRESSED_SCANCODE = 56;
int ALT_RELEASED_SCANCODE = 184;
bool ALT_KEY_PRESSED = false;

/*
int LEFT_ARROW_PRESSED_SCANCODE = 75;
int LEFT_ARROW_RELEASED_SCANCODE = 203;
bool LEFT_ARROW_PRESSED = false;

volatile int num_horizontal_pressed = 0;

int RIGHT_ARROW_PRESSED_SCANCODE = 77;
int RIGHT_ARROW_RELEASED_SCANCODE = 205;
bool RIGHT_ARROW_PRESSED = false;
*/

unsigned char kbdus[256] =
{
	0,				// 0
	27,				// 1
	'1',				// 2
	'2',				// 3	
	'3',				// 4
	'4',				// 5
	'5',				// 6
	'6',				// 7
	'7',				// 8
	'8',				// 9
	'9',				// 10
	'0',				// 11
	'-',				// 12
	'=',				// 13
	'\b',				// 14
	'\t',				// 15
	'q',				// 16
	'w',				// 17
	'e',				// 18
	'r',				// 19
	't',				// 20
	'y',				// 21
	'u',				// 22
	'i',				// 23
	'o',				// 24
	'p',				// 25
	'[',				// 26
	']',				// 27
	'\n',				// 28
	 0, // Control			// 29
	'a',				// 30
	's',				// 31
	'd',				// 32
	'f',				// 33
	'g',				// 34
	'h',				// 35
	'j',				// 36
	'k',				// 37
	'l',				// 38
	';',				// 39
	'\'',				// 40
	'`',				// 41
	0, // Left shift		// 42
	'\\',				// 43
	'z',				// 44
	'x',				// 45
	'c',				// 46
	'v',				// 47
	'b',				// 48
	'n',				// 49
	'm',				// 50
	',',				// 51
	'.',				// 52
	'/',				// 53
	0, // Right shift		// 54
	'*',				// 55
	0, // Alt			// 56
	' ',				// 57
	0, // Caps-Lock			// 58
	0, // F1			// 59
	0, 0, 0, 0, 0, 0, 0, 0,		// 60 - 67
	0, // F10			// 68
	0, // Num Lock			// 69
	0, // Scroll Lock		// 70
	0, // Home Key			// 71
	0, // Up Arrow			// 72
	0, // Page up			// 73
	'-',				// 74
	0, // Left arrow		// 75
	0, 				// 76
	0, // Right arrow		// 77
	'+',				// 78
	0, // End Key			// 79
	0, // Down arrow		// 80
	0, // Page down			// 81
	0, // Insert Key		// 82
	'\v', // Delete key		// 83
	0, 0, 0, 			// 84 - 86
	0, // F11			// 87
	0, // F12			// 88
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 89 - 98
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 99 - 108
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 109 - 118
	0, 0, 0, 0, 0, 0, 0, 0, 0,	// 119 - 127	

	// CAPITAL letters

	0, 				// 129
	27, 				// 130
	'!',				// 131
	'@',				// 132
	'#',				// 133
	'$',				// 134
	'%',				// 135
	'^',				// 136
	'&',				// 137
	'*',				// 138
	'(',				// 139
	')',				// 140
	'_',				// 141
	'+',				// 142
	'\b',				// 143
	'\t',				// 144
	'Q',				// 145
	'W',				// 146
	'E',				// 147
	'R',				// 148
	'T',				// 149
	'Y',				// 150
	'U',				// 151
	'I',				// 152
	'O',				// 153
	'P',				// 154
	'{',				// 155
	'}',				// 156
	'\n',				// 157
	0,				// 158
	'A',				// 159
	'S',				// 160
	'D',				// 161
	'F',				// 162
	'G',				// 163
	'H',				// 164
	'J',				// 165
	'K',				// 166
	'L',				// 167
	':',				// 168
	'"',				// 169
	'~',				// 170
	0,				// 171
	'|',				// 172
	'Z',				// 173
	'X',				// 174
	'C',				// 175
	'V',				// 176
	'B',				// 177
	'N',				// 178
	'M',				// 179
	'<',				// 180
	'>',				// 181
	'?',				// 182
	0,				// 183
	'*',				// 184
	0,				// 185
	' ',				// 186
	0,				// 187
	0,				// 188
	0, 0, 0, 0, 0, 0, 0, 0,		// 189 - 196	
	0,				// 197
	0,				// 198
	0,				// 199
	0,				// 200
	0,				// 201
	0,				// 202
	'-',				// 203
	0,				// 204
	0, 				// 205
	0, 				// 206
	'+',				// 207
	0, 0, 0, '\v', 0, 0, 0, 0, 0,	// 208 - 216
	0, 0, 0, 0, 0, 0, 0, 0, 0,	// 217 - 225
	0, 0, 0, 0, 0, 0, 0, 0, 0,	// 226 - 234
	0, 0, 0, 0, 0, 0, 0, 0, 0,	// 235 - 242
	0, 0, 0, 0, 0, 0, 0, 0, 0, 	// 243 - 251
	0, 0, 0, 0			// 252 - 255 
};

void keyboard_handler(struct regs *r)
{
	unsigned char scancode;

	scancode = inportb(0x60);

	// Key is just released
	if (scancode & 0x80)
	{
		// Shift key
		if ( scancode == LEFT_SHIFT_KEY_RELEASED_SCANCODE || scancode == RIGHT_SHIFT_KEY_RELEASED_SCANCODE ) 
		{
			SHIFT_KEY_PRESSED = false;
		}

		// Control key
		if ( scancode == CONTROL_RELEASED_SCANCODE )
		{ 
			CONTROL_KEY_PRESSED = false;
		}

		// Alt key
		if ( scancode == ALT_RELEASED_SCANCODE )
		{ 
			ALT_KEY_PRESSED = false;
		}

		/*

		// Left Arrow
		if ( scancode == LEFT_ARROW_RELEASED_SCANCODE )
		{ 
			LEFT_ARROW_PRESSED = false;
		}

		// Right Arrow
		if ( scancode == RIGHT_ARROW_RELEASED_SCANCODE )
		{ 
			RIGHT_ARROW_PRESSED = false;
		}
		*/
	}
	else
	{

		// Shift keys
		if ( scancode == LEFT_SHIFT_KEY_PRESSED_SCANCODE || scancode == RIGHT_SHIFT_KEY_PRESSED_SCANCODE )
		{ 
			SHIFT_KEY_PRESSED = true;
		}

		// Caps key
		if ( scancode == CAPS_KEY_PRESSED_SCANCODE ) CAPS_KEY_PRESSED = ! CAPS_KEY_PRESSED;

		// Control key
		if ( scancode == CONTROL_PRESSED_SCANCODE )
		{ 
			CONTROL_KEY_PRESSED = true;
		}

		// Alt key
		if ( scancode == ALT_PRESSED_SCANCODE )
		{ 
			ALT_KEY_PRESSED = true;
		}

		/*
		// Left Arrow
		if ( scancode == LEFT_ARROW_PRESSED_SCANCODE )
		{ 
			LEFT_ARROW_PRESSED = true;
		}

		// Right Arrow
		if ( scancode == RIGHT_ARROW_PRESSED_SCANCODE )
		{ 
			RIGHT_ARROW_PRESSED = true;
		}
		*/

		// Capital letters
		if ( SHIFT_KEY_PRESSED || CAPS_KEY_PRESSED ) scancode = scancode + 128;

		// Print regular character
		if ( kbdus[scancode] != 0 )
		{
			stdinput(kbdus[scancode]);
		}

		// Move cursor when arrows are pressed -- DEACTIVATED
		/*

		if ( LEFT_ARROW_PRESSED && (terminal_getcolumn() - num_horizontal_pressed) > 2 ) 
		{
			num_horizontal_pressed++;
			move_cursor(terminal_getrow(), terminal_getcolumn() - num_horizontal_pressed);
		}

		if ( RIGHT_ARROW_PRESSED && (terminal_getcolumn() - num_horizontal_pressed) < terminal_getcolumn() ) 
		{
			num_horizontal_pressed--;
			move_cursor(terminal_getrow(), terminal_getcolumn() - num_horizontal_pressed);
		}
		*/

	}

}

void keyboard_install()
{
	irq_install_handler(1, keyboard_handler);
}
