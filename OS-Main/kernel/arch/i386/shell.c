#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/shell.h>
#include <kernel/commands.h>

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

void help_command ( ) 
{
	for ( int i = 0; i < numCommands; i ++ )
	{
		printf("%i: %s - %s\n", i, CommandTable[i].name, CommandTable[i].description);
	}
}

void init_shell()
{

	numCommands = 0;

	// Empty "" will also invoke help (the way memcmp works)
	add_new_command("help", "A basic helper function.", help_command);
	add_new_command("cls", "Clear the screen.", clear_screen_command);
	add_new_command("wait", "Wait for 5 seconds.", wait_command);
	add_new_command("reboot", "Restarts the computer.", restart_command);
	
}

void shell()
{

	terminal_startline();

	char* response = gets( );

	int i = findCommand(response);

	if ( i >= 0 )
	{
		void (*command_function)(void) = CommandTable[i].function;
		command_function();
		return;
	}

	printf("Command not found\n");
	return;
	
}

