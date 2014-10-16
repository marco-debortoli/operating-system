#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
 
#if defined(__is_myos_kernel)
#include <kernel/tty.h>
#endif
 
static void print(const char* data, size_t data_length)
{
	for ( size_t i = 0; i < data_length; i++ )
		putchar((int) ((const unsigned char*) data)[i]);
}

char * itoa( int value, char * str, int base )
{
	char * rc;
	char * ptr;
	char * low;

	// Check for supported base.
	// Return null string if invalid.
	if ( base < 2 || base > 36 )
	{
		*str = '\0';
        	return str;
    	}
    	
	rc = ptr = str;

	// Set '-' for negative decimals.
    	if ( value < 0 && base == 10 )
    	{
        	*ptr++ = '-';
    	}
    
	// Remember where the numbers start.
    	low = ptr;
    
	// The actual conversion.
	do
    	{
        	// Modulo is negative for negative value. This trick makes abs() unnecessary.
        	*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        	value /= base;

    	} while ( value );
    
	// Terminating the string.
    	*ptr-- = '\0';
    
	// Invert the numbers.
    	while ( low < ptr )
    	{
        	char tmp = *low;
        	*low++ = *ptr;
        	*ptr-- = tmp;
    	}
    	return rc;
}

int printf(const char* restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);
 
	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;
 
	while ( *format != '\0' )
	{
		if ( *format != '%' )
		{
		print_c:
			amount = 1;
			while ( format[amount] && format[amount] != '%' )
				amount++;
			print(format, amount);
			format += amount;
			written += amount;
			continue;
		}
 
		const char* format_begun_at = format;
 
		if ( *(++format) == '%' )
			goto print_c;
 
		if ( rejected_bad_specifier )
		{
		incomprehensible_conversion:
			rejected_bad_specifier = true;
			format = format_begun_at;
			goto print_c;
		}
 
		if ( *format == 'c' )
		{
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			print(&c, sizeof(c));
		}
		else if ( *format == 's' )
		{
			format++;
			const char* s = va_arg(parameters, const char*);
			print(s, strlen(s));
		}
		else if ( *format == 'i' )
		{
			format++;
			int a = va_arg(parameters, const char*);
			char buffer[32];
			itoa(a, buffer, 10);
			print(buffer, strlen(buffer));
		}
		else
		{
			goto incomprehensible_conversion;
		}
	}
 
	va_end(parameters);
 
	return written;
}

int printchar(char c)
{
	return printf("%c", c);
}
