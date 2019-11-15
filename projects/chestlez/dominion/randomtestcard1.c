#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
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

char inputChar()
{
    return rand()%94 +32;
}

/*
	randomize:
		choice1 0 or 1
		hand cards random 5 between 0 and 26?


*/

void baronTest(int j) {
	int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &state);

	printf("\nTesting Baron Card\n\n");
	printf("\n\n_____TEST %d - player cannot pick up a card when estate pile is empty\n\n", j);

	// copy the game state to a test case
	memcpy(&test, &state, sizeof(struct gameState));

	int player = whoseTurn(&test1);

	state.supplyCount[estate] = rand()%10 +1;
	test.supplyCount[estate] = state.supplyCount[estate];
	  for (i = 0; i < 5; i++)
	{
	  test.hand[player][i] = copper;
	}

	baronHandler(&test, 0, player);

	if (state.supplyCount[estate] == 0) {
		//Check that an estate was not able to be drawn there are none in the pile
		int fail = assert(test.supplyCount[estate], state.supplyCount[estate]);

		if(fail) {
			printf("Failed supply of estates is not 0, player picked up an estate and estate pile was empty\n");
		}
		else {
			printf("Passed estate supply is equal to 0, player did not pick up estate\n");
		}
	}
	else {
		int fail = assert(test.supplyCount[estate] + 1, state.supplyCount[estate]);

		if(fail) {
			printf("Failed - Player should have drawn estate when some are left in pile\n");
		}
		else {
			printf("Passed - estate supply one less than before baronHandler is called when there are estates left\n");
		}
	}
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
    	baronTest(i)
    }

    return 0;
}