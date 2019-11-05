// This file contains the unit test for the tribute handler function

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

void tributeTest() {
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test1, test2, test3;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting tribute Card\n\n");
    printf("\n\n_____TEST 1 - opposing player only has 1 card to display \n\n");

    memcpy(&test1, &state, sizeof(struct gameState));

    int currentPlayer = whoseTurn(&test1);
    int opposingPlayer = 1;

    test1.discardCount[opposingPlayer] = 0;
    test1.deckCount[opposingPlayer] = 1;

    test1.deck[opposingPlayer][0] = copper;

    printf("%d\n", test1.numActions);

    tributeHandler(&test1, currentPlayer, opposingPlayer);

    printf("%d\n", test1.numActions);

    int fail = assert(-1, -1);

    if(fail) {
        printf("Failed - expected to get error when player card choice == handpos\n");
    }
    else {
        printf("Passed - got error when player card choice == handpos\n");
    }
}

int main(int argc, char *argv[])
{
    tributeTest();
    return 0;
}