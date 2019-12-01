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
    int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, testState;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting Bug 10\n\n");
    printf("_____Ambassador cards fails at counting cards above a certain index\n\n");

	// get current player
	int currentPlayer = whoseTurn(&state);
	int handPos = 4;// this is where the test card will go

	// Fill current players hand up with coppers
	for (i = 0; i < 5; i++) {
		state.hand[currentPlayer][i] = copper;
	}
	// add/edit other cards to hand for testing
	state.hand[currentPlayer][handPos] = ambassador; // add test card to hand to play
	state.hand[currentPlayer][2] = feast;
	state.hand[currentPlayer][3] = feast;

	state.supplyCount[feast] = 8;

    memcpy(&testState, &state, sizeof(struct gameState));

	// params for test
	int card = ambassador;
    int choice1 = 2; // there is a feast at hand index 2
    int choice2 = 2;
    int choice3 = 0; // not used for mine
    int bonus = 0; // not used for mine

    cardEffect(card, choice1, choice2, choice3, &testState, handPos, &bonus);

    int fail = assert(state.supplyCount[feast] + 1, testState.supplyCount[feast]);

    if(fail) {
        printf("Failed - 2 feasts were not returned\n");
    }
    else {
        printf("Passed - 2 feast cards successfully returned\n");
    }
}

int main(int argc, char *argv[])
{
    bugTest();
    return 0;
}