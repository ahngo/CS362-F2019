#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

// Bug #1 unit test
// Mine has improper flag passed to discardCard()
// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
// mine: trash a treasure to gain a treasure costing up to 3 coins more
// choice1: hand position of card to trash
// choice2: enum of treasure to gain

int main() 
{
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
    
    G.hand[thisPlayer][0] = mine;
    G.hand[thisPlayer][1] = copper;
    choice1 = 1;
    choice2 = silver;
    
    // copy control state to test state
    memcpy(&testG, &G, sizeof(struct gameState));
    
    // Play Mine: trash Copper in hand slot 1 to gain Silver
    
    printf("Testing Bug #1: Mine has improper flag passed to discardCard()\n");
    int test = cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    verify("Playing the card was successful", test != -1);
    
    // Look through played pile to make sure card was trashed
    for (int i = 0; i < testG.playedCardCount; i++)
    {
        //printf("%s, ", cardname(testG.hand[thisPlayer][i]));
        verify("Card not trashed properly",  testG.playedCards[i] != copper);
    }
    
    /* Print hand contents
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        printf("%s, ", cardname(testG.hand[thisPlayer][i]));
    }
    printf("\n");
    */
    
	return 0;
}


