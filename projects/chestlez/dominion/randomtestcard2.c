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

void minionTest(int j, int* passed) {
    int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

	printf("\n\n_____TEST %d\n\n", j + 1);
    memcpy(&test, &state, sizeof(struct gameState));

    int currentPlayer = whoseTurn(&test);
    int choice1 = rand()%2;
    int choice2;
    //must use one of these choices
    if (choice1) {
    	choice2 = 0;
    }
    else {
    	choice2 = 1;
    }

    int handPos = rand()%5;

      for (i = 0; i < 5; i++)
    {
      test.hand[currentPlayer][i] = copper;
    }
    test.hand[currentPlayer][handPos] = minion;

    minionHandler(&test, choice1, choice2, currentPlayer, handPos);

	if (choice1) {
		printf("Player should gain 2 coins \n");
		//player should gain 2 coins
		int fail = assert(test.coins, state.coins + 2);

		if(fail) {
			printf("Failed - does not gain 2 coins when choice1 is true\n");
		}
		else {
			printf("Passed - gains 2 coins when choice1 is true\n");
			*passed = *passed + 1;
		}
	}
	else {
		printf("Player should draw 4 cards from deck\n");
		//player should discard and then gain 4, as well as the other player should
		int fail = assert(test.deckCount[currentPlayer], state.deckCount[currentPlayer] - 4);

		if(fail) {
			printf("Failed - player does not draw 4 cards from deck\n");
		}
		else {
			printf("Passed - player draws 4 cards from deck the correct number \n");
			*passed = *passed + 1;
		}
	}
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    printf("\nTesting Minion Card\n\n");
    int passed = 0;
    int tests = 1;
    for (int i = 0; i < tests; i++) {
    	printf("%d\n", passed);
    	minionTest(i, &passed);
    }
    printf("test passed: %d out of %d ", passed, tests);

    return 0;
}