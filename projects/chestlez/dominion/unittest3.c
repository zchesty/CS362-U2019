// This file contains the unit test for the ambassador handler function

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

void ambassadorTest() {
    int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test1, test2, test3;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting Ambassador Card\n\n");
    printf("\n\n_____TEST 1 - player player picks up 4 cards when they choose \n\n");

    memcpy(&test1, &state, sizeof(struct gameState));

    int currentPlayer = whoseTurn(&test1);
    int choice1 = 1;
    int choice2 = 0;
    int handPos = 4;


    state.supplyCount[estate] = 0;
    test1.supplyCount[estate] = 0;
      for (i = 0; i < 5; i++)
    {
      test1.hand[currentPlayer][i] = copper;
    }
    test1.hand[currentPlayer][handPos] = minion;

    minionHandler(&test1, choice1, choice2, currentPlayer, handPos);

    //Check that an estate was not able to be drawn there are none in the pile
    int fail = assert(test1.coins, state.coins + 2);

    if(fail) {
        printf("Failed - does not gain 2 coins when choice1 is true\n");
    }
    else {
        printf("Passed - gains 2 coins when choice1 is true\n");
    }
}

int main(int argc, char *argv[])
{
    ambassadorTest();
    return 0;
}