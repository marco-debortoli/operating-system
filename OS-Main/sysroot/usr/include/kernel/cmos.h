/*

	The Header File for the live time
	Base class: arch/i386/cmos/cmos.c

*/

#ifndef _KERNEL_CMOS_H
#define _KERNEL_CMOS_H

#include <stdint.h>

struct utimeval {
	uint32_t tv_sec;
	uint32_t tv_usec;
};

struct timeval {
	uint16_t year;
	uint16_t month;
	uint16_t day;
	uint16_t hour;
	uint16_t minute;
	uint16_t second;
};

void get_time(uint16_t* hours, uint16_t* minutes, uint16_t* seconds);
void get_date(uint16_t* year, uint16_t* month, uint16_t* days);
int gettimeofday(struct utimeval* t, void* z);
uint32_t now();

#endif
