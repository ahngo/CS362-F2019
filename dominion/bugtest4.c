#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

// Bug #4 unit test
// isGameOver() function does not check through all 26 cards
// int isGameOver(struct gameState *state)
// returns 1 if more than 3 supply piles are exhausted, 0 otherwise


int main() 
{
    printf("Testing Bug #4: isGameOver() does not check 27th card supply pile\n");

    // initialize game variables, state and test state
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize game/test state
	initializeGame(numPlayers, k, seed, &G);
    
    // initialize/manipulate game variables, set up test state
    // int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    // int thisPlayer = 0;
    
    // test case - supply piles for cards 24, 25, and 26 are empty
    
    G.supplyCount[24] = 0;
    G.supplyCount[25] = 0;
    G.supplyCount[26] = 0;
    
    // run isGameOver and verify against expected results
    int gameover = isGameOver(&G);
    verify("isGameOver() checks card #27", gameover == 1);

	return 0;
}


