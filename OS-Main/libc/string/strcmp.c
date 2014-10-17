#include <string.h>

// Compare two strings. Return 0 if they are equal or 1 otherwise.
int strcmp(char *str1, char *str2)
{
	int i = 0;
	int status = 0;

	// Null terminator required!
	while ( str1[i] != '\0' && str2[i] != '\0' )
	{
		if( str1[i] != str2[i] )
		{
			status = 1;
			break;
        	}
        	
		i++;
      	}

	if ( (str1[i] == '\0' && str2[i] != '\0') || ( str1[i] != '\0' && str2[i] == '\0' ) )
        	status = 1;
  
	return status;
}
