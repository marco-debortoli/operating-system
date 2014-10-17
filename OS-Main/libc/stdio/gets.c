#include <stdio.h>
#include <string.h>

volatile char buffer[MAX_COMMAND_LENGTH];
volatile int idx = -1;

// Resets all buffer values to 0
void clearBuffer ( )
{
	for ( int i = 0; i < MAX_COMMAND_LENGTH; i++ )
	{
		if ( buffer[i] != 0 ) buffer[i] = 0;
		else break;
	}
}

// Gets input from the keyboard
char* gets( )
{
	idx = -1;
	clearBuffer();
	
	// Definitely not the optimal way to do it lol
	while ( buffer[ idx<0 ? 0 : idx ] != '\n' );

	buffer[idx] = 0;

	return buffer;
}

// From the stdinput function
void sendToGets(char c)
{

	if ( c == '\t' ) return;
	if ( c == '\b' )
	{
		if ( idx == -1 ) return;		

		buffer[idx] = 0;
		idx--;
		return;
	}

	idx++;
	buffer[idx] = c;
}

