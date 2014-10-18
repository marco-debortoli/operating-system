#include <string.h>

// Write len copies of val into dest.
void memset(size_t *dest, size_t val, size_t len)
{
	size_t *temp = (size_t *)dest;

	for ( ; len != 0; len--) 
	{
		*temp++ = val;
	}
}
