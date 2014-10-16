/*

	The Header File for the timer
	Base class: arch/i386/timer.c

*/

#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

#include <stddef.h>
#include <stdint.h>

void timer_install();
void timer_wait(int seconds);
int timer_uptime();

#endif
