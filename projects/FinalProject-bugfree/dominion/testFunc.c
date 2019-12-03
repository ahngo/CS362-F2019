#include <stdio.h>

int verify(char* purpose, int check)
{
    if (check)
    {
        //printf("Passed test: %s\n", purpose);
        return 0;
    }
    else 
    {
        printf("** FAILED test: %s\n", purpose);
    }
    return -1;
}

char* cardname(int card)
{
    char* cardname[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", 
    "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", 
    "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
    
    return cardname[card];
}


