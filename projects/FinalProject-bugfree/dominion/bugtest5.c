#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

// Bug #4 unit test
// scoreFor() function using discard count instead of deck count
// int scoreFor (int player, struct gameState *state)


int main() 
{
    printf("Testing Bug #5: scoreFor() function using discard count instead of deck count\n");

    // initialize game variables, state and test state
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize game/test state
	initializeGame(numPlayers, k, seed, &G);
    
    // initialize/manipulate game variables, set up test state
    //int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int thisPlayer = 0;
    
    // test case - only one estate in hand (1 vp)
    G.hand[thisPlayer][0] = estate;
    
    // rest of hand is copper
    int handCount = G.handCount[thisPlayer];
    for (int i = 0; i < handCount; i++)
    {
        G.hand[thisPlayer][i+1] = copper;
    }
    
    // one duchy in discard pile (3 vp)
    G.discardCount[thisPlayer]++;
    G.discard[thisPlayer][0] = duchy;
    
    G.deckCount[thisPlayer] = 5;
    for (int i = 0; i < 5; i++)
    {
        G.deck[thisPlayer][i] = estate;
    }
    
    
    // run scorefor and verify against expected results
    // 6 estates + 1 duchy should equal 9 vp
    int score = scoreFor(thisPlayer, &G);
    verify("scoreFor() calculates score correctly", score == 9);

	return 0;
}


