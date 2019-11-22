#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include "testFunc.h"
#define MAX_TESTS 500
#define NUM_CARDS 26
#define NOISY 0 

// Tribute random test
// int tribute_function(int currentPlayer, int nextPlayer, int* tributeRevealedCards, struct gameState *state)

void generateRandomGameVars(int* handpos, int* choice1, int* choice2, int* numPlayers, int* seed, int* thisPlayer)
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

// Create random deck count and deck for a player
// Return number of cards in deck
int randomizeTopTwoCards(int thisPlayer, struct gameState* G)
{
    int randomDeckCount = rand() % 10;
    G->deckCount[thisPlayer] = randomDeckCount;
    
    // 
    for (int i = 0; i < randomDeckCount; i++)
    {
        G->deck[thisPlayer][i] = rand() % NUM_CARDS;
    }
    
    // if no cards in deck, set cards to -1
    if (randomDeckCount == 0)
    {
        G->deck[thisPlayer][0] = -1;
        G->deck[thisPlayer][1] = -1;
    }
    // if 1 card in deck, set second card to -1
    else if (randomDeckCount < 2)
    {
        G->deck[thisPlayer][1] = -1;
    }
    // 10% chance of making the cards duplicate for testing
    int makeCardsDupe = rand() % 10;
    if (makeCardsDupe == 0 && randomDeckCount > 1)
    {
        G->deck[thisPlayer][1] = G->deck[thisPlayer][0];
    }
    
    return randomDeckCount;
}

int main() 
{
    srand(time(NULL));
    
    int handpos = 0, choice1 = 0, choice2 = 0; 
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int tributeRevealedCards[2] = {-1, -1};
	
	// variables to count expected bonuses
	int expectedBonusActions;
	int expectedBonusCoins;
	int expectedBonusCards;
    // check for treasure/victory cards
    int treasureCards[] = {copper, silver, gold};
    int treasureCardsLen = sizeof(treasureCards) / sizeof(int);
    int victoryCards[] = {estate, duchy, province, gardens, great_hall};
    int victoryCardsLen = sizeof(victoryCards) / sizeof(int);
    // array to print out an actual card name instead of enum
    char* cardname[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", 
    "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", 
    "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

	printf("***** TESTING TRIBUTE *****\n\n");
	
	for (int i = 0; i < MAX_TESTS; i++)
	{
	    // randomize game variables
    	generateRandomGameVars(&handpos, &choice1, &choice2, &numPlayers, &seed, &thisPlayer);
    	expectedBonusActions = 0;
    	expectedBonusCoins = 0;
    	expectedBonusCards = 0;
    	initializeGame(numPlayers, k, seed, &G);
    	// random player hand
    	generateRandomHand(thisPlayer, &G);
    	// create a tribute in hand
    	if (G.handCount[thisPlayer] != 0)
    	{
        	handpos = rand() % G.handCount[thisPlayer];
        	G.hand[thisPlayer][handpos] = tribute;
    	}
    	// define other player to watch their variables
    	otherPlayer = thisPlayer + 1;
        if (otherPlayer > numPlayers - 1)
        {
            otherPlayer = 0;
        }
        // randomize other player's deck
        int numCardsInOtherDeck = randomizeTopTwoCards(otherPlayer, &G);
        int numCardsTributed = 0;
        // count how many cards should be tributed
        if (numCardsInOtherDeck >= 2)
        {
            numCardsTributed = 2;
        }
        else
        {
            numCardsTributed = numCardsInOtherDeck;
        }
        // check if cards are duplicated
        int duplicateTribute = 0;
        if (G.deck[otherPlayer][0] == G.deck[otherPlayer][1])
        {
             duplicateTribute = 1;
             numCardsTributed--;
        }
        // keep track of tributed cards in order to print out their names
        int testcard1 = G.deck[otherPlayer][0];
        int testcard2 = G.deck[otherPlayer][1];
        // count expected bonuses
        for (int i = 0; i < numCardsTributed; i++)
        {
            int treasureCard = 0;
            int victoryCard = 0;
            
            int checkCard = G.deck[otherPlayer][i];
            
            if (checkCard == curse || checkCard == -1)
            {
                continue;
            }
            
            for (int j = 0; j < treasureCardsLen; j++)
            {
                if (checkCard == treasureCards[j])
                {
                    expectedBonusCoins += 2;
                    treasureCard = 1;
                }
            }
            for (int k = 0; k < victoryCardsLen; k++)
            {
                if (checkCard == victoryCards[k])
                {
                    expectedBonusCards += 2;
                    victoryCard = 1;
                }
            }
            if (treasureCard == 0 && victoryCard == 0)
            {
                expectedBonusActions += 2;
            }
        }
        // call Tribute function
        memcpy(&testG, &G, sizeof(struct gameState));
        tribute_function(thisPlayer, otherPlayer, &tributeRevealedCards, &testG);
        
        int test1, test2, test3;
        
        printf("Start of new trial:\n\n");
        
        // Adjust control state variables for easy comparison
        // Playing Tribute is an action
        G.numActions--;
        // Tribute is discarded after playing
        G.handCount[thisPlayer]--;
        
        // Verify bonus actions
        test1 = verify("Bonus actions match expectations", ((testG.numActions - expectedBonusActions) == 0));
        if (test1 == -1)
        {
            //printf("Actions expected: %i, Actual actions: %i\n", (G.numActions - 1 + expectedBonusActions), testG.numActions);
            printf("expectedBonusActions: %i, Test State actions: %i, Control State actions: %i\n", expectedBonusActions, testG.numActions, G.numActions);
        }
        
        // Verify bonus coins
        // Bonus coins should be the difference between test state and control state
        test2 = verify("Bonus coins match expectations", expectedBonusCoins == (testG.coins - G.coins));
        if (test2 == -1)
        {
            //printf("Coins expected: %i, Actual coins: %i\n", expectedBonusCoins, testG.coins);
            printf("expectedBonusCoins: %i, Test State coins: %i, Control State coins: %i\n", expectedBonusCoins, testG.coins, G.coins);
        }
        
        // Verify bonus cards
        // Bonus cards should be difference between test state and control state
        test3 = verify("Bonus cards match expectations", (testG.handCount[thisPlayer] - expectedBonusCards == G.handCount[thisPlayer]));
        if (test3 == -1)
        {
            //printf("Bonus cards expected: %i, Actual bonus cards: %i\n", expectedBonusCards, testG.handCount[thisPlayer] - (G.handCount[thisPlayer] - 1));
            printf("expectedBonusCards: %i, Test State cards: %i, Control State cards: %i\n", expectedBonusCards, testG.handCount[thisPlayer], G.handCount[thisPlayer]);
        }
        
        // Print out variables for failing tests
        if (test1 == -1 || test2 == -1 || test3 == -1)
        {
            printf("Test failure cards: %i cards in deck. Top cards: %s, %s\n", numCardsInOtherDeck, cardname[testcard1], cardname[testcard2]);
            if (duplicateTribute && testcard1 != -1)
            {
                printf("* Tribute cards are duplicate.\n");
            }
        }
        
        printf("\nEnd of trial.\n\n");
	}
	return 0;
}


