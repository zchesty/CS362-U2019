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

void baronTest(int j, int* passed) {

	printf("%d", *passed);
	int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &state);

	printf("\n\n_____TEST %d\n\n", j + 1);

	// copy the game state to a test case
	memcpy(&test, &state, sizeof(struct gameState));

	int player = whoseTurn(&test);
	int choice1 = rand()%2;
	state.supplyCount[estate] = rand()%10;
	test.supplyCount[estate] = state.supplyCount[estate];
	  for (i = 0; i < 5; i++)
	{
	  test.hand[player][i] = rand()%27;
	}
	int hasEstate = 0;
	for (i = 0; i < 5; i++)
	{
		if (test.hand[player][i] == estate) {
	  		hasEstate = 1;
	  		break;
		}
	}

	baronHandler(&test, choice1, player);

	if (state.supplyCount[estate] > 0 && choice1 == 0) {
	printf("Choice1 = 1 estates count is greater than 0 player should gain 1 estate\n");
		int fail = assert(test.supplyCount[estate] + 1, state.supplyCount[estate]);
		if(fail) {
			printf("Failed - estate supply count did not go down by 1\n");
		}
		else {
			printf("Passed - estate supply one less than before baronHandler is called when there are estates left\n");
			*passed = *passed + 1;
		}
	}
	else if (choice1 == 0) {
		printf("Choice1 = 0 supply of estates = 0, player should not gain estate\n");
		int fail = assert(test.supplyCount[estate], state.supplyCount[estate]);

		if(fail) {
			printf("Failed supply of estates is 0, player picked up an estate and estate pile was empty\n");
		}
		else {
			printf("Passed estate supply is equal to 0, player did not pick up estate\n");
			*passed = *passed + 1;
		}
	}
	else if (choice1 == 1 && hasEstate == 1) {
		//gain 4 coins
		printf("Choice1 = 1 hasEstate = 1 player should  gain 4 coins\n");
		int fail = assert(test.coins, state.coins + 4);

		if(fail) {
			printf("Failed player should have gained 4 coins.\n");
		}
		else {
			printf("Passed player gains 4 coins when they have estate\n");
			*passed = *passed + 1;
		}
	}
	else if (choice1 == 1 && hasEstate == 0) {
		printf("Choice1 = 1 hasEstate = 0 player should not gain 4 coins\n");
		//no gain 4 coins
		int fail = assert(test.coins, state.coins);

		if(fail) {
			printf("Failed player gained 4 coins when they has no estate\n");
		}
		else {
			printf("Passed player did not get 4 coins\n");
			*passed = *passed + 1;
		}
    	}
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    printf("\nTesting Baron Card\n\n");
    int passed = 1;
    int tests = 100;
    for (int i = 0; i < tests; i++) {
    	printf("%d\n", passed);
    	baronTest(i, &passed);
    }
    printf("test passed: %d out of %d ", passed, tests);

    return 0;
}