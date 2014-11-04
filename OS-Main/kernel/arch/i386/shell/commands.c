#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/timer.h>
#include <kernel/reboot.h>
#include <kernel/cmos.h>
#include <kernel/heap.h>

void clear_screen_command ( )
{

	uint16_t VGA_HEIGHT = 25;

	for ( uint16_t i = 1; i < VGA_HEIGHT - 1; i++ )
	{
		clear_line(i);
		terminal_reset();
	}
}

void wait_command ( )
{
	timer_wait(5);
}

void get_date_command ( )
{
	uint16_t year = 0;
	uint16_t month = 0;
	uint16_t day = 0;

	get_date(&year, &month, &day);
	
	printf("Date (month/day/year): %s%i/%s%i/%i\n", (month > 10) ? "" : "0", month, (day > 10) ? "" : "0", day, year);

}

void get_time_command ( )
{
	uint16_t hour = 0;
	uint16_t minute = 0;
	uint16_t second = 0;

	get_time(&hour, &minute, &second);


	// Subtract 4 off hour for time zone correction
	printf("Time: %i:%s%i:%s%i\n", hour - 4, (minute > 10) ? "" : "0", minute, (second > 10) ? "" : "0", second);
}

void restart_command ( )
{
	printf("Rebooting in 5 seconds\n");

	// TODO - Eventually add way to stop rebooting

	timer_wait(5);
	reboot();
}
	
