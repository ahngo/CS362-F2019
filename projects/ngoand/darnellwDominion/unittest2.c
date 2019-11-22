#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

// Minion unit test
// int minion_function(int choice1, int choice2, int j, struct gameState *state, int handPos, int currentPlayer)
// choice1: +1 Action, +2 Coins
// choice2: Discard hand and draw 4 cards. All other players with hands >= 5 cards do the same.

int main() 
{
    int handpos = 0, choice1 = 0, choice2 = 0; 
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int j = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    
    // +1 Action, +2 Coins
    printf("Testing Minion Case: +1 Action, +2 Coins\n");
    choice1 = 1;
    minion_function(choice1, choice2, j, &testG, handpos, thisPlayer);
    verify("+1 Actions", (testG.numActions == G.numActions + 1));
	verify("+2 Coins", (testG.coins == G.coins + 2));
	
	// All players discard hand and gain 4 cards
	printf("Testing Minion Case: All players discard hand and gain 4 cards\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 1;
	int otherPlayer = thisPlayer + 1;
	int currentPlayerHandCount = testG.handCount[thisPlayer];
	testG.handCount[otherPlayer] = 5;
	for (int i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		testG.hand[thisPlayer][i] = -1;
	}
	minion_function(choice1, choice2, j, &testG, handpos, thisPlayer);
	verify("Cards gained from deck for current player", (testG.hand[thisPlayer][0] != -1));
	verify("Cards correctly discarded for current player", (testG.discardCount == G.discardCount + currentPlayerHandCount));
	verify("Hand count for current player is 4", testG.handCount[thisPlayer] == 4);
	verify("Cards gained from deck for other player", (testG.hand[thisPlayer + 1][0] != -1));
	verify("Hand count for other player is 4", testG.handCount[thisPlayer + 1] == 4);
	
	// Only current player discards hand and draws 4
	printf("Testing Minion Case: Only current player discards hand and draws 4\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 1;
	testG.handCount[otherPlayer] = 3;
	for (int i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		testG.hand[thisPlayer][i] = -1;
	}
	minion_function(choice1, choice2, j, &testG, handpos, thisPlayer);
	verify("Cards gained from deck for current player", (testG.hand[thisPlayer][0] != -1));
	verify("Cards correctly discarded for current player", (testG.discardCount == G.discardCount + currentPlayerHandCount));
	verify("Hand count for current player is the same", testG.handCount[otherPlayer] == 3);
	verify("Other player did not discard hand", testG.discardCount[otherPlayer] == G.discardCount[otherPlayer]);

	return 0;
}


