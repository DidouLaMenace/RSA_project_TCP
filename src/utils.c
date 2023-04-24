#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Get the authentification message from the client without the \0 and any space before and after the message
void clear_str(char* str)
{
    int start = 0;
    int end = strlen(str) - 1;

    // Remove space before the message
    while (isspace(str[start]))
    {
        start++;
    }

    // Remove space after the message
    while ((end >= start) && isspace(str[end]))
    {
        end--;
    }

    // Move remaining characters to start of string
    int i;
    for (i = start; i <= end; i++)
    {
        str[i - start] = str[i];
    }
    str[i - start] = '\0';
}