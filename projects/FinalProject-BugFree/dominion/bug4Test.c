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

void bugTest() {
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting Bug 04 \n\n");
    printf("_____is game over checks all cards for end game condition - function should return true 3 piles empty\n\n");

	// setup supply piles

	state.supplyCount[baron] = 0;
	state.supplyCount[minion] = 0;
	state.supplyCount[treasure_map] = 0;

	int gameOver = isGameOver(&state);

	// played card count should be equal to state.playedCardCount + 1
	// The only card that will be in played card count is the actual mine card
    int fail = assert(gameOver , 1);

    if(fail) {
        printf("Failed - isGameOver returned false \n");
    }
    else {
        printf("Passed - isGameOver returned true\n");
    }
}

int main(int argc, char *argv[])
{
    bugTest();
    return 0;
}