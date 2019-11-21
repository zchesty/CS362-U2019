// This file contains the unit test for the mine handler function

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

void mineTest() {
    int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test1, test2;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting mine Card\n\n");
    printf("\n\n_____TEST 1 - able to pick up silver from copper (card costing within 3 from trash card)\n\n");

    memcpy(&test1, &state, sizeof(struct gameState));

    int currentPlayer = whoseTurn(&test1);
    int choice1 = 0;
    int choice2 = silver;


	  for (i = 0; i < 5; i++)
	{
	  test1.hand[currentPlayer][i] = copper;
	}
	int handPos = 5;
    int mineResponse = mineCardEffect(choice1, choice2, currentPlayer, handPos, &test1);

    updateCoins(currentPlayer, &test1, 0);

    int fail = assert(test1.coins, 7);

    if(fail) {
        printf("Failed - unable able to pick up card that is within 3 cost above trash card\n");
    }
    else {
        printf("Passed -  able to pick up card that is within 3 cost above trash card\n");
    }

        printf("\n\n_____TEST 2 - able to pick up gold from silver ( card costing within 3 from trash card)\n\n");

        memcpy(&test2, &state, sizeof(struct gameState));

        currentPlayer = whoseTurn(&test2);
        choice1 = 0;
        choice2 = gold;

    	  for (i = 0; i < 5; i++)
    	{
    	  test2.hand[currentPlayer][i] = silver;
    	}

        int initPlayedCount = test2.playedCardCount;
		mineResponse = mineCardEffect(choice1, choice2, currentPlayer, handPos, &test2);

        updateCoins(currentPlayer, &test2, 0);

        fail = assert(test2.coins, 11);

        if(fail) {
            printf("Failed - unable able to pick up card that is within 3 cost above trash card\n");
        }
        else {
            printf("Passed -  able to pick up card that is within 3 cost above trash card\n");
        }

    printf("\n\n_____TEST 3 - trashed card goes to the trash \n\n");

    fail = assert(test2.playedCardCount, initPlayedCount);

    if(fail) {
        printf("Failed - card should not enter played pile\n");
    }
    else {
        printf("Passed - card does not enter played pile\n");
    }
}

int main(int argc, char *argv[])
{
    mineTest();
    return 0;
}