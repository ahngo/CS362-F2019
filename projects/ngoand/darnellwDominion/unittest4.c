#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "testFunc.h"

// Tribute unit test
// int tribute_function(int currentPlayer, int nextPlayer, int* tributeRevealedCards, struct gameState *state)


int main() 
{
    int handpos = 0; 
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int otherPlayer = thisPlayer + 1;
	int tributeRevealedCards[2] = {-1, -1};
	initializeGame(numPlayers, k, seed, &G);
    
    
    // 0 cards in next player's deck
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Tribute Case: 0 Cards in next player's deck\n");
    testG.deckCount[otherPlayer] = 0;
    tribute_function(thisPlayer, otherPlayer, &tributeRevealedCards, &testG);
    verify("No bonus actions", testG.numActions == G.numActions);
    verify("No bonus coins", testG.coins == G.coins);
    // Account for played Tribute card
    verify("No bonus cards", testG.handCount[thisPlayer] + 1 == G.handCount[thisPlayer]);
    
    // 1 card in next player's deck
    // Test for action bonus
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Tribute Case: 1 Card in next player's deck, of each type\n");
    testG.deckCount[otherPlayer] = 1;
    testG.deck[otherPlayer][0] = tribute;
    testG.discardCount[otherPlayer] = 0;
    tribute_function(thisPlayer, otherPlayer, &tributeRevealedCards, &testG);
    // Account for action that Tribute used
    verify("2 bonus actions", testG.numActions == G.numActions + 2);
    verify("Action card: No bonus coins", testG.coins == G.coins);
    verify("Action card: No bonus cards", testG.handCount[thisPlayer] + 1 == G.handCount[thisPlayer]);
    // Test for coin bonus
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[otherPlayer] = 1;
    testG.deck[otherPlayer][0] = copper;
    testG.discardCount[otherPlayer] = 0;
    tribute_function(thisPlayer, otherPlayer, &tributeRevealedCards, &testG);
    verify("Treasure card: No bonus cards", testG.handCount[thisPlayer] + 1 == G.handCount[thisPlayer]);
    verify("Treasure card: No bonus actions", testG.numActions == G.numActions);
    verify("Treasure card: Bonus coins", testG.coins == G.coins + 2);
    // Test for card bonus
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[otherPlayer] = 1;
    testG.deck[otherPlayer][0] = estate;
    testG.discardCount[otherPlayer] = 0;
    tribute_function(thisPlayer, otherPlayer, &tributeRevealedCards, &testG);
    // Account for played Tribute card
    verify("Victory card: Bonus cards", testG.handCount[thisPlayer] - 1 == G.handCount[thisPlayer]);
    verify("Victory card: No bonus actions", testG.numActions == G.numActions);
    verify("Victory card: No bonus coins", testG.coins == G.coins);
    
    // 0 card in deck and 1 card in discard pile
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Tribute Case: 0 cards in next player's deck and 1 in discard\n");
    testG.deckCount[otherPlayer] = 0;
    testG.discardCount[otherPlayer] = 1;
    testG.discard[otherPlayer][0] = tribute;
    tribute_function(thisPlayer, otherPlayer, &tributeRevealedCards, &testG);
    // Account for action that Tribute used
    verify("2 bonus actions", testG.numActions == G.numActions + 2);
    verify("Action card: No bonus coins", testG.coins == G.coins);
    verify("Action card: No bonus cards", testG.handCount[thisPlayer] + 1 == G.handCount[thisPlayer]);
    verify("No cards in deck for other player", testG.deckCount[otherPlayer] == 0);
    verify("One card in discard pile for other player", testG.discardCount[otherPlayer] == 1);
    
    // 2 cards in next player's deck of different types
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Tribute Case: 2 cards in next player's deck, of each type\n");
    testG.deckCount[otherPlayer] = 2;
    testG.deck[otherPlayer][0] = tribute;
    testG.deck[otherPlayer][1] = estate;
    testG.discardCount[otherPlayer] = 0;
    tribute_function(thisPlayer, otherPlayer, &tributeRevealedCards, &testG);
    verify("Victory card: Bonus cards", testG.handCount[thisPlayer] - 1 == G.handCount[thisPlayer]);
    verify("2 bonus actions", testG.numActions == G.numActions + 2);
    verify("Other player discarded top cards", testG.discardCount[otherPlayer] == 2);
    
    // 2 cards in next player's deck are the same card
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing Tribute Case: 2 cards in next player's deck, of each type\n");
    testG.deckCount[otherPlayer] = 2;
    testG.deck[otherPlayer][0] = silver;
    testG.deck[otherPlayer][1] = silver;
    testG.discardCount[otherPlayer] = 0;
    tribute_function(thisPlayer, otherPlayer, &tributeRevealedCards, &testG);
    verify("Duplicate card check (treasure)", testG.coins == G.coins + 2);
    verify("Duplicate card check: no bonus actions", testG.numActions == G.numActions);
    verify("Treasure card: Bonus coins", testG.coins == G.coins + 2);
    verify("Treasure card: No bonus cards", testG.handCount[thisPlayer] + 1 == G.handCount[thisPlayer]);
    
	return 0;
}


