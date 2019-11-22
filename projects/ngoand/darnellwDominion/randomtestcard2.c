#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include "testFunc.h"
#define MAX_TESTS 100
#define NUM_CARDS 28
#define NOISY 0 

// Minion random test
// int cardEffectMinion(int choice1, int choice2, struct gameState *state, int currentPlayer, int handPos)

void generateRandomGameVarsMinion(int* handpos, int* choice1, int* choice2, int* numPlayers, int* seed, int* thisPlayer)
{
    *handpos = rand() % MAX_HAND;
    *choice1 = rand() % 2;
    *choice2 = rand() % 2;
    // 2 to 4 players
    *numPlayers = rand() % 3 + 2;
    *seed = rand() % 1000 + 1;
    *thisPlayer = rand() % (*numPlayers + 1);
}

void generateRandomHand(int thisPlayer, struct gameState* G)
{
    int randomHandCount = rand() % 10;
    if (randomHandCount == 0)
    {
        randomHandCount++;
    }
    G->handCount[thisPlayer] = randomHandCount;
    
    for (int i = 0; i < randomHandCount; i++)
    {
        G->hand[thisPlayer][i] = rand() % NUM_CARDS;
    }
}

void printErrorVars(int result, int handpos, int choice1, int numPlayers, int thisPlayer)
{
    if (result >= 0)
    {
        return;
    }
    else if (result < 0 && NOISY)
    {
        printf("handpos %i, choice1 %i, numPlayers %i, thisPlayer %i\n", handpos, choice1, numPlayers, thisPlayer);
    }
}

int main() 
{
    srand(time(NULL));
    
    int handpos = 0, choice1 = 0, choice2 = 0; 
    int seed = 1000;
    int j = 0;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	
	printf("***** TESTING MINION *****\n\n");
	
	for (int i = 0; i < MAX_TESTS; i++)
	{
	    // Randomize game variables and player hand
    	generateRandomGameVarsMinion(&handpos, &choice1, &choice2, &numPlayers, &seed, &thisPlayer);
    	initializeGame(numPlayers, k, seed, &G);
    	generateRandomHand(thisPlayer, &G);
    	// Create a minion in hand
    	if (G.handCount[thisPlayer] != 0)
    	{
    	    handpos = rand() % G.handCount[thisPlayer];
    	    G.hand[thisPlayer][handpos] = minion;
    	}
    	
        memcpy(&testG, &G, sizeof(struct gameState));
        // Define other player
        otherPlayer = thisPlayer + 1;
        if (otherPlayer > numPlayers - 1)
        {
            otherPlayer = 0;
        }
        // Generate hand for other player
        generateRandomHand(otherPlayer, &testG);
        int otherPlayerHandCount = testG.handCount[otherPlayer];
            
        minion_function(choice1, choice2, j, &testG, handpos, thisPlayer);
        
        // choice1: +1 Actions, +2 Coins
        if (choice1 == 1)
        {
           verify("Case: choice1 true: +1 Actions", (testG.numActions == G.numActions + 1));
    	   verify("Case: choice1 true: +2 Coins", (testG.coins == G.coins + 2));
        }
        // choice2: Discard hand and draw 4; any players with hand size >=5 do the same
        else if (choice2 == 1)
        {
            
            verify("Case: choice2 true: Cards correctly discarded for current player", (testG.discardCount == G.discardCount + testG.handCount[thisPlayer]));
            verify("Case: choice2 true: Hand count for current player is 4", testG.handCount[thisPlayer] == 4);
            
            if (otherPlayerHandCount >= 5)
            {
                verify("Case: choice2 true and other player has >= 5 cards in hand: Hand discarded", (testG.discardCount[otherPlayer]) > G.discardCount[otherPlayer]);
                verify("Case: choice2 true and other player has >= 5 cards in hand: Hand count for other player is 4", testG.handCount[otherPlayer] == 4);
            }
            else if (otherPlayerHandCount < 5)
            {
                verify("Case: choice2 true and other player has <5 cards in hand: Hand count for other player did not change", testG.handCount[otherPlayer] == otherPlayerHandCount);
                verify("Case: choice2 true and other player has <5 cards in hand: Other player did not discard hand", testG.discardCount[otherPlayer] == G.discardCount[otherPlayer]);
            }
        }
	}
	return 0;
}


