/*

	Header file for standard I/O operations
	Base Class: libc/stdio -> printf.c -> putchar.c -> puts.c

*/

#ifndef _STDIO_H
#define _STDIO_H 1
 
#include <sys/cdefs.h>
#define MAX_COMMAND_LENGTH 500
 
#ifdef __cplusplus
extern "C" {
#endif

void sendToGets(char);
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);
char* itoa(long long value, char * str, int base);
int printchar(char c);
char* gets();
void stdinput(char);
 
#ifdef __cplusplus
}
#endif
 
#endif
