/*

	Installs the timer

*/

#include <stddef.h>
#include <stdint.h>

void timer_install();
void timer_wait(int seconds);
int timer_uptime();
void timer_wait_ticks(int ticks);
