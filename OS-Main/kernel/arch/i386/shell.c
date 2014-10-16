#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/shell.h>

command_table_t CommandTable[MAX_COMMANDS];
int numCommands = 0;

void add_new_command(char *name, char* description, void *function)
{
	if ( numCommands < MAX_COMMANDS - 1 )
	{
		CommandTable[numCommands].name = name;
		CommandTable[numCommands].description = description;
		CommandTable[numCommands].function = function;

		numCommands++;
	}
}


int findCommand(char* command)
{
	int ret;

	for ( int i = 0; i < numCommands; i++)
	{

		ret = memcmp(command, CommandTable[i].name, strlen(command));
		if ( ret == 0 ) return i;
	}
	
	return -1;
}


void help_command()
{
	printf("TEST\n");
}

void empty_command()
{
}

void init_shell()
{

	numCommands = 0;
	add_new_command("help\n", "A basic helper function.", help_command);
	add_new_command("", "", empty_command);

}

void shell()
{

	terminal_startline();

	char* str = "";

	gets(str);

	printf("%i", strlen(str));

	int i = findCommand(str);

	if ( i >= 0 )
	{
		void (*command_function)(void) = CommandTable[i].function;
		command_function();
		return;
	}
	
	printf("Command not found\n");
	return;
	
}

