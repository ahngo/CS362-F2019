#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

// Returns random character from ASCII 32 to 125 but any uppercase characters
// are converted into lowercase.

char inputChar()
{
    // ' ' = ASCII 32 (space)
    // '}' = ASCII 125
    // Generate random character from ASCII 32 to 125
    char randomChar = 32 + (rand() % 94);
    
    // convert any uppercase to lowercase
    if (isalpha(randomChar))
    {
        randomChar = tolower(randomChar);
    }
    
    return randomChar;
}

// Returns a random string of 5 letters followed by a null terminator
char *inputString()
{
    // input pool
    char* secretString = "the testers rest";
    // generate random string from input pool
    char randomString[6];
    char secretStrLen = strlen(secretString);
    for (int i = 0; i < 5; i++)
    {
        randomString[i]  = (secretString[rand() % secretStrLen]);
    }
    randomString[6] = '\0';
    
    char* ranStr = randomString;
    return ranStr;
    
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
