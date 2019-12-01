#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

// Bug #10 unit test
// Ambassador has improper coding when checking proper amount of cards to return to supply
// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
// ambassador: Reveal a card from your hand and choose up to 2 copies to return to the supply.
// each other player gains a copy of that card.
// choice1: hand position of card to reveal
// choice2: number of cards to return to the supply

int main() 
{
    printf("Testing Bug #10: Ambassador has improper coding when checking proper amount of cards to return to supply\n");

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
    
    // test case
    // hand contains 2 curses and an ambassador
    // play ambassador in handpos 2, reveal curse in handpos 0, return curses in 0 and 1
    G.handCount[thisPlayer] = 3;
    G.hand[thisPlayer][0] = curse;
    G.hand[thisPlayer][1] = curse;
    G.hand[thisPlayer][2] = ambassador;
    handpos = 2;
    choice2 = 2;
    
    // copy control state to test state
    memcpy(&testG, &G, sizeof(struct gameState));
    // Play ambassador: should return both curses to the supply
    cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    // check for both curses to be returned
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        int test = verify("Cards properly returned", testG.hand[thisPlayer][i] != curse);
        if (test < 0) break;
        //printf("%s\n", cardname((testG.hand[thisPlayer][i])));
    }
    
	return 0;
}


