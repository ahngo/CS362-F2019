#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

#define TESTCARD "mine"

// int mine_function(int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus, int j, int currentPlayer)
// choice1 = chosen treasure to trash
// choice2 = chosen treasure to gain

int main() 
{
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0; 
    int seed = 1000;
    int numPlayers = 2;
    int j = 0;
    int bonus = 0;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    
    // Test invalid choices
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Mine Case: Choosing invalid cards\n");
    testG.hand[thisPlayer][1] = curse;
    choice1 = 1;
    choice2 = silver;
    verify("Choose invalid card to trash", mine_function(choice1, choice2, choice3, &testG, handpos, &bonus, j, thisPlayer) == -1);
    testG.hand[thisPlayer][1] = silver;
    choice2 = estate;
    verify("Choose invalid card to gain", mine_function(choice1, choice2, choice3, &testG, handpos, &bonus, j, thisPlayer) == -1);
    testG.hand[thisPlayer][1] = copper;
    choice2 = gold;
    verify("Choose treasure too expensive", mine_function(choice1, choice2, choice3, &testG, handpos, &bonus, j, thisPlayer) == -1);
    
    // Test proper interaction of cards
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Mine Case: Valid choices and card interactions\n");
    testG.hand[thisPlayer][0] = copper;
    testG.hand[thisPlayer][1] = copper;
    choice1 = 0;
    choice2 = silver;
    int test = mine_function(choice1, choice2, choice3, &testG, handpos, &bonus, j, thisPlayer);
    verify("Correct amount of cards discarded", testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1);
    verify("Check for valid case: Copper to Silver", test != -1);
    
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][1] = silver;
    testG.hand[thisPlayer][2] = silver;
    choice1 = 0;
    choice2 = gold;
    test = mine_function(choice1, choice2, choice3, &testG, handpos, &bonus, j, thisPlayer);
    verify("Adding new treasure to discard pile", testG.discard[thisPlayer][0] == gold);
    verify("Check for valid case: Silver to Gold", test != -1);
    
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][1] = gold;
    testG.hand[thisPlayer][2] = curse;
    choice1 = 1;
    choice2 = copper;
    test = mine_function(choice1, choice2, choice3, &testG, handpos, &bonus, j, thisPlayer);
    verify("Trash Gold to gain Copper", testG.hand[thisPlayer][1] != gold);
    verify("Check for valid case: Gold to Copper", test != -1);
    
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][1] = copper;
    testG.hand[thisPlayer][2] = curse;
    choice1 = 1;
    choice2 = copper;
    test = mine_function(choice1, choice2, choice3, &testG, handpos, &bonus, j, thisPlayer);
    verify("Trash Copper to gain Copper", testG.hand[thisPlayer][1] != copper);
    verify("Check for valid case: Copper to Copper", test != -1);

	return 0;
}


