// This file contains the unit test for the minion handler function

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

void minionTest() {
    int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test1, test2;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting Minion Card\n\n");
    printf("\n\n_____TEST 1 - player gains 2 coins when they choose choice1 \n\n");

    memcpy(&test1, &state, sizeof(struct gameState));

    int currentPlayer = whoseTurn(&test1);
    int choice1 = 1;
    int choice2 = 0;
    int handPos = 4;

      for (i = 0; i < 5; i++)
    {
      test1.hand[currentPlayer][i] = copper;
    }
    test1.hand[currentPlayer][handPos] = minion;

   minionCardEffect(handPos, currentPlayer, choice1, choice2, &test1);

    int fail = assert(test1.coins, state.coins + 2);

    if(fail) {
        printf("Failed - does not gain 2 coins when choice1 is true\n");
    }
    else {
        printf("Passed - gains 2 coins when choice1 is true\n");
    }

    printf("\n\n_____TEST 2 - player picks up 4 cards when they choose choice2\n\n");

    memcpy(&test2, &state, sizeof(struct gameState));

    currentPlayer = whoseTurn(&test1);
    choice1 = 0;
    choice2 = 1;
    handPos = 4;

      for (i = 0; i < 5; i++)
    {
      test2.hand[currentPlayer][i] = copper;
    }
    test2.hand[currentPlayer][handPos] = minion;

   test2.handCount[1] = 4;

    int opposingDeckCount = test2.deckCount[1] ;// opposing player number

   minionCardEffect(handPos, currentPlayer, choice1, choice2, &test2);


    fail = assert(test2.deckCount[currentPlayer],state.deckCount[currentPlayer] - 4);

    if(fail) {
        printf("Failed - player does not draw 4 cards from deck\n");
    }
    else {
        printf("Passed - player draws 4 cards from deck the correct number \n");
    }

    printf("\n\n_____TEST 3 - opposing players do not draw if they have 4 cards\n\n");


    fail = assert(opposingDeckCount,test2.deckCount[1]);

        if(fail) {
            printf("Failed - opposint player is drawing when they only have 4 cards in hand\n");
        }
        else {
            printf("Passed - opposing players are not drawing when they have 4 cards in hand\n");
        }




}

int main(int argc, char *argv[])
{
    minionTest();
    return 0;
}