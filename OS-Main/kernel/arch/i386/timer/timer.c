/*

	Timer (PIT) functionality -- IRQ0

*/

// Note: currently using default 18.2222Hz as frequency

#include <kernel/descriptor_tables.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/portio.h>
#include <stdio.h>
#include <kernel/timer.h>

volatile int timer_ticks = 0;

// Called as IRQ 0
void timer_handler(struct regs *r)
{
	timer_ticks++;
}

void timer_wait_ticks(int ticks)
{
	volatile int eticks;
	eticks = timer_ticks + ticks;

	while(timer_ticks < eticks);
}

// Wait for a desired number of seconds
void timer_wait(int seconds)
{
	int ticks = seconds * 18;
	timer_wait_ticks(ticks);
}

// Registers the PIT as IRQ 0
void timer_install()
{
	irq_install_handler(0, timer_handler);
}

// Returns the uptime of the CPU (how many seconds it has been running for)
int timer_uptime()
{
	return timer_ticks / 18 ;
}
