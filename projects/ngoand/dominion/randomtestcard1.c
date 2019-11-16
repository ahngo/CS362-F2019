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

// Baron random test
// int cardEffectBaron(int choice1, struct gameState *state, int currentPlayer, int handPos)

void generateRandomGameVars(int* handpos, int* choice1, int* numPlayers, int* seed, int* thisPlayer)
{
    *handpos = rand() % MAX_HAND;
    *choice1 = rand() % 2;
    // 2 to 4 players
    *numPlayers = rand() % 3 + 2;
    *seed = rand() % 1000 + 1;
    *thisPlayer = rand() % (*numPlayers + 1);
}

void generateRandomHand(int thisPlayer, struct gameState* G)
{
    int randomHandCount = rand() % MAX_HAND;
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
    
    int handpos = 0, choice1 = 0; 
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int result = 0;		

	printf("***** TESTING BARON *****\n\n");
	
	for (int i = 0; i < MAX_TESTS; i++)
	{
	    // Randomize game variables
    	generateRandomGameVars(&handpos, &choice1, &numPlayers, &seed, &thisPlayer);
    	initializeGame(numPlayers, k, seed, &G);
    	// Randomize player hand and create a Baron
    	generateRandomHand(thisPlayer, &G);
    	
    	if (G.handCount[thisPlayer] != 0)
    	{
        	handpos = rand() % G.handCount[thisPlayer];
        	G.hand[thisPlayer][handpos] = baron;
    	}
        memcpy(&testG, &G, sizeof(struct gameState));
        cardEffectBaron(choice1, &testG, thisPlayer, handpos);
        
        // Player gains one buy regardless in any case
        verify("+1 buy", (testG.numBuys == G.numBuys + 1));
        
        // if choice1 = 0, gain an estate
        // if choice1 = discard an estate for 4 coins, else gain an estate
        // Gain an Estate
        if (choice1 == 0)
        {
            result = verify("Case: Gain an Estate: Supply loses ONE Estate", (testG.supplyCount[estate] == G.supplyCount[estate] - 1));
            printErrorVars(result, handpos, choice1, numPlayers, thisPlayer);
            result = verify("Case: Gain an Estate: Player gains Estate to discard pile", (testG.discardCount[thisPlayer] > G.discardCount[thisPlayer]));
            printErrorVars(result, handpos, choice1, numPlayers, thisPlayer);
            continue;
        }
        // Choose to discard an Estate for 4 coins
        else if (choice1 == 1)
        {
            // check to see if Estate exists in hand
            int handCount = testG.handCount[thisPlayer];
            int handHasEstate = 0;
            for (int i = 0; i < handCount; i++)
            {
                if (testG.hand[thisPlayer][i] == estate)
                {
                    handHasEstate = 1;
                    break;
                }
            }
            // Discard Estate and gain 4 coins
            if (handHasEstate == 1)
            {
                result = verify("Case: Discard Estate with Estate in hand: Player gains 4 coins", (testG.coins == G.coins + 4));
                printErrorVars(result, handpos, choice1, numPlayers, thisPlayer);
                result = verify("Case: Discard Estate with Estate in hand: Player hand loses a card", (testG.handCount[thisPlayer] < G.handCount[thisPlayer]));
                printErrorVars(result, handpos, choice1, numPlayers, thisPlayer);
            }
            // No Estates in hand; gain an Estate
            else if (handHasEstate == 0)
            {
                result = verify("Case: Discard Estate without Estate in hand: Player should NOT gain 4 coins", (testG.coins == G.coins));
                printErrorVars(result, handpos, choice1, numPlayers, thisPlayer);
                result = verify("Case: Discard Estate without Estate in hand: Supply loses ONE Estate", (testG.supplyCount[estate] == G.supplyCount[estate] - 1));
                printErrorVars(result, handpos, choice1, numPlayers, thisPlayer);
                result = verify("Case: Discard Estate without Estate in hand: Player gains Estate to discard pile", (testG.discardCount[thisPlayer] > G.discardCount[thisPlayer]));
                printErrorVars(result, handpos, choice1, numPlayers, thisPlayer);
            }
        }
	}
	return 0;
}


