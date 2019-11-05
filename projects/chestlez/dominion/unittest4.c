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
    printf("\n\n_____TEST 1 - opposing player only has 1 card to display should gain 2 coins and nothing else \n\n");

    memcpy(&test1, &state, sizeof(struct gameState));

    int currentPlayer = whoseTurn(&test1);
    int opposingPlayer = 1;

    test1.discardCount[opposingPlayer] = 0;
    test1.deckCount[opposingPlayer] = 1;

    test1.deck[opposingPlayer][0] = copper;

    printf("%d\n", test1.coins);

    tributeHandler(&test1, currentPlayer, opposingPlayer);

    printf("%d\n", test1.coins);

    int fail = assert(test1.coins, state.coins + 2);

    if(fail) {
        printf("Failed - player should gain 2 coins\n");
    }
    else {
        printf("Passed - player gains 2 coins\n");
    }
    fail = assert(test1.numActions, state.numActions);

    if(fail) {
            printf("Failed - player should not have gained any actions\n");
        }
        else {
            printf("Passed - player should did gain any actions\n");
        }
}

int main(int argc, char *argv[])
{
    tributeTest();
    return 0;
}