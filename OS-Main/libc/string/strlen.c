#include <string.h>

// Gets the length of a string
size_t strlen(const char* string)
{
	size_t result = 0;
	while ( string[result] )
		result++;
	return result;
}
