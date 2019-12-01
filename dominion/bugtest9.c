#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

// Bug #9 unit test
// Tribute has improper handling of duplicate cards
// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
// tribute: player to your left (next player) reveals then discards the top 2 cards of his deck
// action card = +2 actions, victory card = +2 cards, treasure card = +2 coins

int main() 
{
    printf("Testing Bug #9: Tribute has improper handling of duplicate cards\n");

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
    int nextPlayer = 1;
    
    // check next player's deck to contain 2 coppers
    G.deckCount[nextPlayer] = 3;
    G.deck[nextPlayer][0] = copper;
    G.deck[nextPlayer][1] = copper;
    G.deck[nextPlayer][2] = copper;
    
    // copy control state to test state
    memcpy(&testG, &G, sizeof(struct gameState));
    // Play Tribute: should get 2 coins, no actions and no cards
    cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
    verify("Tribute grants proper coins", testG.coins = G.coins + 2);
    verify("Tribute should not grant bonus actions", testG.numActions == 1);
	return 0;
}


