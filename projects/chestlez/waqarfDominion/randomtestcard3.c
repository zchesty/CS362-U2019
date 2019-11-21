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

void tributeTest(int j, int* passed) {
	printf("%d", *passed);
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

	printf("\n\n_____TEST %d\n\n", j + 1);

	memcpy(&test, &state, sizeof(struct gameState));

	int currentPlayer = whoseTurn(&test);
	int opposingPlayer = 1;

	test.discardCount[opposingPlayer] = 0;
	test.deckCount[opposingPlayer] = 2;

	test.deck[opposingPlayer][0] = rand()%27;
	test.deck[opposingPlayer][1] = rand()%27;

	int card1 = test.deck[opposingPlayer][0];
	int card2 = test.deck[opposingPlayer][1];

	tributeCardEffect(opposingPlayer, currentPlayer, &test);

	//cards are the same
	if (card1 == card2) {
		if (card1 == copper || card1 == silver || card1 == gold) {
			//player should get 2 coins
			printf("Player should gain 2 coins cards were the same treasure \n");
			int fail = assert(test.coins, state.coins + 2);

			if(fail) {
				printf("Failed - player should gain 2 coins\n");
			}
			else {
				printf("Passed - player gains 2 coins\n");
				*passed = *passed + 1;
			}
		}
		else if (card1 == estate || card1 == duchy || card1 == province || card1 == gardens || card1== great_hall) {
			// player should gain 2 cards
			printf("Player should gain 2 cards cards were the same victory \n");
			int fail = assert(test.handCount[currentPlayer], state.handCount[currentPlayer] + 2);

			if(fail) {
				printf("Failed - player should gain 2 cards\n");
			}
			else {
				printf("Passed - player gains 2 cards\n");
				*passed = *passed + 1;
			}
		}
		else {
			//player should gain 2 actions
			printf("Player should gain 2 actions cards were the same victory \n");
			int fail = assert(test.numActions, state.numActions + 2);

			if(fail) {
				printf("Failed - player should gain 2 action\n");
			}
			else {
				printf("Passed - player gains 2 actions\n");
				*passed = *passed + 1;
			}
		}
	}
	//cards are different
	else {
		// 2 coin cards
		if ((card1 == copper || card1 == silver || card1 == gold) && (card2 == copper || card2 == silver || card2 == gold)) {
			// player should gain 4 coins
			printf("Player should gain 4 coins cards were both treasure \n");
			int fail = assert(test.coins, state.coins + 4);

			if(fail) {
				printf("Failed - player should gain 4 coins\n");
			}
			else {
				printf("Passed - player gains 4 coins\n");
			}
		}
		//card 1 is coin card 2 is victory
		else if ((card1 == copper || card1 == silver || card1 == gold) && (card2 == estate || card2 == duchy || card2 == province || card2 == gardens || card2 == great_hall)) {
			//player should gain 2 coins and 2 cards
			printf("Player should gain 2 coins and 2 cards -  cards were treasure and victory \n");
			int fail = (assert(test.coins, state.coins + 2) && assert(test.handCount[currentPlayer], state.handCount[currentPlayer] + 2));

			if(fail) {
				printf("Failed - player should gain 2 coins and 2 cards\n");
			}
			else {
				printf("Passed - player did not gains 2 coins and 2 cards\n");
				*passed = *passed + 1;
			}
		}
		// card 1 is coin card 2 is action
		else if (card1 == copper || card1 == silver || card1 == gold) {
			//player should gain 2 coins and 2 actions
			printf("Player should gain 2 coins and 2 actions -  cards were treasure and action \n");
			int fail = (assert(test.coins, state.coins + 2) && assert(test.numActions, state.numActions + 2));

			if(fail) {
				printf("Failed - player should gain 2 coins and 2 actions\n");
			}
			else {
				printf("Passed - player did not gains 2 coins and 2 actions\n");
				*passed = *passed + 1;
			}
		}
		//card1 is victory card2 is coins
		else if ((card1 == estate || card1 == duchy || card1 == province || card1 == gardens || card1== great_hall) && (card2 == copper || card2 == silver || card2 == gold)) {
			//player should gain 2 coins and 2 cards
			printf("Player should gain 2 coins and 2 cards -  cards were treasure and victory \n");
			int fail = (assert(test.coins, state.coins + 2) && assert(test.handCount[currentPlayer], state.handCount[currentPlayer] + 2));

			if(fail) {
				printf("Failed - player should gain 2 coins and 2 cards\n");
			}
			else {
				printf("Passed - player did not gains 2 coins and 2 cards\n");
				*passed = *passed + 1;
			}
		}
		// 2 vicotry cards
		else if ((card1 == estate || card1 == duchy || card1 == province || card1 == gardens || card1== great_hall) && (card2 == estate || card2 == duchy || card2 == province || card2 == gardens || card2 == great_hall)) {
			//player should gain 4 cards
			printf("Player should gain 4 cards cards were both victory \n");
			int fail = assert(test.handCount[currentPlayer], state.handCount[currentPlayer] + 4);

			if(fail) {
				printf("Failed - player should gain 4 cards\n");
			}
			else {
				printf("Passed - player gains 4 cards\n");
				*passed = *passed + 1;
			}
		}
		// card1 victory card 2 is action
		else if (card1 == estate || card1 == duchy || card1 == province || card1 == gardens || card1== great_hall) {
			//player should gain 2 cards and 2 actions
			printf("Player should gain 2 cards and 2 actions -  cards were victory and action \n");
			int fail = (assert(test.handCount[currentPlayer], state.handCount[currentPlayer] + 2) && assert(test.numActions, state.numActions + 2));

			if (fail) {
				printf("Failed - player should gain 2 coins and 2 actions\n");
			}
			else {
				printf("Passed - player did not gains 2 coins and 2 actions\n");
				*passed = *passed + 1;
			}
		}
		// card 1 is action card 2 is coin
		else if (card2 == copper || card2 == silver || card2 == gold) {
			//player should gain 2 coins and 2 actions
			printf("Player should gain 2 coins and 2 actions -  cards were treasure and action \n");
			int fail = (assert(test.coins, state.coins + 2) && assert(test.numActions, state.numActions + 2));

			if(fail) {
				printf("Failed - player should gain 2 coins and 2 actions\n");
			}
			else {
				printf("Passed - player did not gains 2 coins and 2 actions\n");
				*passed = *passed + 1;
			}
		}
		// card 1 is action card 2 is victory
		else if (card2 == estate || card2 == duchy || card2 == province || card2 == gardens || card2 == great_hall) {
			//player should gain 2 cards and 2 actions
			printf("Player should gain 2 cards and 2 actions -  cards were victory and action \n");
			int fail = (assert(test.handCount[currentPlayer], state.handCount[currentPlayer] + 2) && assert(test.numActions, state.numActions + 2));

			if(fail) {
				printf("Failed - player should gain 2 coins and 2 actions\n");
			}
			else {
				printf("Passed - player did not gains 2 coins and 2 actions\n");
				*passed = *passed + 1;
			}
		}
		// 2 action
		else {
			// player should gain 4 actions
			printf("Player should gain 4 actions cards were both actions \n");
			int fail = assert(test.numActions, state.numActions + 4);

			if(fail) {
				printf("Failed - player should gain 4 action\n");
			}
			else {
				printf("Passed - player gains 4 actions\n");
				*passed = *passed + 1;
			}
		}

	}
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
	printf("\nTesting tribute Card\n\n");
    int passed = 0;
    int tests = 10;
    for (int i = 0; i < tests; i++) {
    	tributeTest(i, &passed);
    }
    printf("test passed: %d out of %d ", passed, tests);

    return 0;
}