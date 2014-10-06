#ifndef _STDIO_H
#define _STDIO_H 1
 
#include <sys/cdefs.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);
char* itoa(int value, char * str, int base);
int printchar(char c);
 
#ifdef __cplusplus
}
#endif
 
#endif
