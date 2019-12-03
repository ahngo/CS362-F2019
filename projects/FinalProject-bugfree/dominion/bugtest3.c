#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

// Bug #3 unit test
// Mine has improper cost comparison
// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
// remodel: trash a card to gain a card costing up to 2 coins more
// choice1: hand position of card to trash
// choice2: enum of card to gain

int main() 
{
    printf("Testing Bug #3: Remodel has improper cost comparison\n");

    // initialize game variables, state and test state
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize game/test state
	initializeGame(numPlayers, k, seed, &G);
    
    // initialize/manipulate game variables, set up test state
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int thisPlayer = 0;
    
    G.hand[thisPlayer][0] = remodel;
    G.hand[thisPlayer][1] = copper;
    choice1 = 1;
    choice2 = copper;
    
    // copy control state to test state
    memcpy(&testG, &G, sizeof(struct gameState));
    
    // Play Mine: trash Copper in hand slot 1 to gain Copper
    int test = cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);
    verify("Trash Copper to gain Copper", test != -1);

	return 0;
}


