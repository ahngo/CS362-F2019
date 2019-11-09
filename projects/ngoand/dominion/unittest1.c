#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

// Baron unit test
// int cardEffectBaron(int choice1, struct gameState *state, int currentPlayer, int handPos)

int main() 
{
    int handpos = 0, choice1 = 0; 
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

    memcpy(&testG, &G, sizeof(struct gameState));
    
    // +1 Buy, gain an Estate
    printf("Testing Baron Case: Gain an Estate\n");
    cardEffectBaron(choice1, &testG, thisPlayer, handpos);
    //cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
    verify("+1 buy", (testG.numBuys == G.numBuys + 1));
    verify("Supply loses ONE Estate", (testG.supplyCount[estate] == G.supplyCount[estate] - 1));
    verify("Player gains Estate to discard pile", (testG.discardCount[thisPlayer] > G.discardCount[thisPlayer]));
    
    // Discard an Estate with an Estate in hand
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Baron Case: Discard an Estate for 4 coins\n");
    choice1 = 1;
    testG.hand[thisPlayer][1] = estate;
    cardEffectBaron(choice1, &testG, thisPlayer, handpos);
    verify("+1 buy", (testG.numBuys == G.numBuys + 1));
    verify("Player gains 4 coins", (testG.coins == G.coins + 4));
    verify("Player hand loses a card", (testG.handCount[thisPlayer] < G.handCount[thisPlayer]));
    
    // Try to discard Estate with none in hand
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Baron Case: Try to discard Estate with none in hand\n");
    choice1 = 1;
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        testG.hand[thisPlayer][i] = silver;
    }
    cardEffectBaron(choice1, &testG, thisPlayer, handpos);
    verify("Player should NOT gain 4 coins", (testG.coins == G.coins));
    verify("Supply loses ONE Estate", (testG.supplyCount[estate] == G.supplyCount[estate] - 1));
    verify("Player gains Estate to discard pile", (testG.discardCount[thisPlayer] > G.discardCount[thisPlayer]));
    
    // Gain Estate but none are left in supply
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Baron Case: Gain Estate but none are left in supply\n");
    choice1 = 0;
    testG.supplyCount[estate] = 0;
    cardEffectBaron(choice1, &testG, thisPlayer, handpos);
    verify("Supply of Estates should stay 0", (testG.supplyCount[estate] == 0));

	return 0;
}


