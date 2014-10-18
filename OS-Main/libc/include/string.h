/*

	Header file for basic string functions (mandatory string functions)
	Base Class: libc/string/ -> memcmp.c -> memcpy.c -> memmove.c -> memset.c -> strlen.c

*/

#ifndef _STRING_H
#define _STRING_H 1
 
#include <sys/cdefs.h>
 
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void memset(size_t* dest, size_t val, size_t len);
size_t strlen(const char*);
int strcmp(char* str1, char* str2);
char* strcat(char *dest, const char *src);

#ifdef __cplusplus
}
#endif
#endif
