#include <stdio.h>

int verify(char* purpose, int check)
{
    if (check)
    {
        printf("Passed test: %s\n", purpose);
        return 1;
    }
    else 
    {
        printf("** FAILED test: %s\n", purpose);
    }
    return 0;
}