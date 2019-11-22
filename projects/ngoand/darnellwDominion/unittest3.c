#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

// Ambassador unit test
// int ambassador_function(int choice1, int choice2, int j, int handPos, struct gameState *state, int currentPlayer)
// choice1 = chosen card to reveal, choice2 = num of cards to return to supply

int main() 
{
    int handpos = 0, choice1 = 0, choice2 = 0; 
    int seed = 1000;
    int numPlayers = 2;
    int j = 0;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int otherPlayer = thisPlayer + 1;
	int numOtherPlayers = numPlayers - 1;
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    
    // Return 0 Estates to Supply
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Ambassador Case: Return 0 Estates to Supply\n");
    choice1 = 1;
    choice2 = 0;
    testG.hand[thisPlayer][1] = estate;
    testG.hand[thisPlayer][2] = silver;
    ambassador_function(choice1, choice2, j, handpos, &testG, thisPlayer);
    verify("One Estate is given to each other player", testG.discardCount[otherPlayer] > G.discardCount[otherPlayer]);
    verify("Current player's Estate is still there", testG.hand[thisPlayer][1] == estate);
    verify("Ambassador was discarded correctly", testG.discardCount[thisPlayer] > G.discardCount[thisPlayer]);
    
    // Return 1 Estate to Supply
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Ambassador Case: Return 1 Estate to Supply\n");
    choice1 = 1;
    choice2 = 1;
    testG.hand[thisPlayer][1] = estate;
    testG.hand[thisPlayer][2] = silver;
    ambassador_function(choice1, choice2, j, handpos, &testG, thisPlayer);
    verify("One Estate is given to each other player", testG.discardCount[otherPlayer] > G.discardCount[otherPlayer]);
    verify("Current player's Estate is no longer there", testG.hand[thisPlayer][1] != estate);
    verify("Supply count of Estates is correct", testG.supplyCount[estate] == G.supplyCount[estate]);
    
    // Return 2 Estates to Supply
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Ambassador Case: Return 2 Estates to Supply\n");
    choice1 = 1;
    choice2 = 2;
    testG.hand[thisPlayer][1] = estate;
    testG.hand[thisPlayer][2] = estate;
    testG.hand[thisPlayer][3] = silver;
    ambassador_function(choice1, choice2, j, handpos, &testG, thisPlayer);
    verify("One Estate is given to each other player", testG.discardCount[otherPlayer] > G.discardCount[otherPlayer]);
    verify("Current player's Estates are no longer there", testG.hand[thisPlayer][2] != estate);
    verify("Supply count of Estates is correct", testG.supplyCount[estate] - choice2 - numOtherPlayers == G.supplyCount[estate]);
    
    // Try to return 2 Estates to Supply while having only 1 in hand
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Ambassador Case: Return 2 Estates to Supply but with only 1 in hand\n");
    choice1 = 1;
    choice2 = 2;
    testG.hand[thisPlayer][0] = ambassador;
    testG.hand[thisPlayer][1] = estate;
    for (int i = 2; i < testG.handCount[thisPlayer]; i++)
    {
    	testG.hand[thisPlayer][i] = curse;
    }
    int test = ambassador_function(choice1, choice2, j, handpos, &testG, thisPlayer);
    verify("Should return -1", test == -1);
    
	return 0;
}


