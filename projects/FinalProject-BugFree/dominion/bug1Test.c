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

void bug1Test() {
    int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, testState;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting Bug 1 - mine card Card\n\n");
    printf("_____Coin card is sent to the trash and is no longer in game play\n\n");

	// get current player
	int currentPlayer = whoseTurn(&state);
	int handPos = 4;// this is where the mine card will go

	// Fill current players hand up with
	for (i = 0; i < 5; i++) {
		state.hand[currentPlayer][i] = copper;
	}
	state.hand[currentPlayer][handPos] = mine; // add a mine card to hand to play

    memcpy(&testState, &state, sizeof(struct gameState));

	// params for test
	int card = mine;
    int choice1 = 0; // there is a copper at hand index 0
    int choice2 = silver;
    int choice3 = 0; // not used for mine
    int bonus = 0; // not used for mine

    cardEffect(card, choice1, choice2, choice3, &testState, handPos, &bonus);

	// played card count should be equal to state.playedCardCount + 1
	// The only card that will be in played card count is the actual mine card
    int fail = assert(state.playedCardCount + 1 , testState.playedCardCount);

    if(fail) {
        printf("Failed - Coin card is still in game play, it is in the playedCardCount instead of trash\n");
    }
    else {
        printf("Passed - Coin card is no longer in game play, it was sent to the trash\n");
    }
}

int main(int argc, char *argv[])
{
    bug1Test();
    return 0;
}