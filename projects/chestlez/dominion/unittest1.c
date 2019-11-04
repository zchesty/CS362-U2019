// This file contains the unit test for th baron handler function

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int assert(int got, int want) {
    if (got != want) {
        return 1;
    }
    else {
        return 0;
    }
}


void baronTest() {
	int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test1, test2, test3;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &state);

	printf("\nTesting Baron Card\n\n");
	printf("\n\n_____TEST 1 - player cannot pick up a card when estate pile is empty\n\n");

	// copy the game state to a test case
	memcpy(&test1, &state, sizeof(struct gameState));

	int player = whoseTurn(&test1);

	state.supplyCount[estate] = 0;
	test1.supplyCount[estate] = 0;
	  for (i = 0; i < 5; i++)
	{
	  test1.hand[player][i] = copper;
	}
	
	baronHandler(&test1, 0, player);

	//Check that an estate was not able to be drawn there are none in the pile
	int fail = assert(test1.supplyCount[estate], state.supplyCount[estate]);

	if(fail) {
		printf("Failed supply of estates is not 0, player picked up an estate and estate pile was empty\n");
	}
	else {
		printf("Passed estate supply is equal to 0, player did not pick up estate\n");
	}

	printf("\n\n_____TEST 2 - Player Gets 4 coins when they have an estate card in hand\n\n");
	state.supplyCount[estate] = 8;

	// copy the game state to a test case
    	memcpy(&test2, &state, sizeof(struct gameState));

    	player = whoseTurn(&test2);

    	state.supplyCount[estate] = 0;
    	test2.supplyCount[estate] = 0;
    	  for (i = 0; i < 4; i++)
    	{
    	  test2.hand[player][i] = copper;
    	}
    	test2.hand[player][i] = estate;

        int initCoin = test2.coins;
    	baronHandler(&test2, 1, player);

    	fail = assert(initCoin + 4, test2.coins);

        if(fail) {
            printf("Failed player did not gain 4 coins with estate in hand\n");
        }
        else {
            printf("Passed player gained 4 coins with estate in hand\n");
        }
        
        printf("\n\n_____TEST 3 - Player does not Get 4 coins when they do not have an estate card in hand\n\n");
        	state.supplyCount[estate] = 8;
        
        	// copy the game state to a test case
            	memcpy(&test3, &state, sizeof(struct gameState));
        
            	player = whoseTurn(&test3);
        
            	state.supplyCount[estate] = 0;
            	test3.supplyCount[estate] = 0;
            	  for (i = 0; i < 5; i++)
            	{
            	  test3.hand[player][i] = copper;
            	}
        
                initCoin = test3.coins;
            	baronHandler(&test3, 1, player);
        
            	fail = assert(initCoin, test3.coins);
        
                if(fail) {
                    printf("Failed player should not gain 4 coins with no estate in hand\n");
                }
                else {
                    printf("Passed player did not gain 4 coins with estate in hand\n");
                }
}

int main(int argc, char *argv[])
{
    baronTest();
    return 0;
}