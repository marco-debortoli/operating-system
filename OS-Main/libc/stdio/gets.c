#include <stdio.h>
#include <string.h>

volatile char buffer[500];
volatile int idx = -1;

// Gets input from the keyboard
char* gets( char* str )
{
	idx = -1;
	
	// Definitely not the optimal way to do it lol
	while ( buffer[ idx<0 ? 0 : idx ] != '\n' );


	for ( int i = 0; i < idx; i++ )
	{
		*str++ = buffer[i];
	}

	return str;
}

// From the stdinput function
void sendToGets(char c)
{

	if ( c == '\b' || c == '\t' ) return;
	idx++;
	buffer[idx] = c;
}

