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

    printf("\nTesting Bug 07\n\n");
    printf("_____player gains 4 coins when the revealed cards are a copper and a gold and gains no other benefits\n\n");

	// get current player
	int currentPlayer = whoseTurn(&state);
	int opposingPlayer = 1;
	int handPos = 4;// this is where the test card will go

	state.discardCount[opposingPlayer] = 0;
	state.deckCount[opposingPlayer] = 2;

	state.deck[opposingPlayer][0] = copper;
	state.deck[opposingPlayer][1] = gold;

	// Fill current players hand up with coppers
	for (i = 0; i < 5; i++) {
		state.hand[currentPlayer][i] = copper;
	}
	// add/edit other cards to hand for testing
	state.hand[currentPlayer][handPos] = tribute; // add test card to hand to play

    memcpy(&testState, &state, sizeof(struct gameState));

	// params for test
	int card = tribute;
    int choice1 = 0; // not used for tribute
    int choice2 = 0; // not used for tribute
    int choice3 = 0; // not used for tribute
    int bonus = 0; // not used for tribute

    cardEffect(card, choice1, choice2, choice3, &testState, handPos, &bonus);

	int fail = assert(testState.coins, state.coins + 4);

    if(fail) {
        printf("Failed - player should gain 4 coins\n");
    }
    else {
        printf("Passed - player gains 4 coins\n");
    }
    fail = assert(testState.numActions, state.numActions);

    if(fail) {
            printf("Failed - player should not have gained any actions\n");
        }
        else {
            printf("Passed - player did not gain any actions\n");
        }
}

int main(int argc, char *argv[])
{
    bugTest();
    return 0;
}
