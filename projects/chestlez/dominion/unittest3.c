// This file contains the unit test for the ambassador handler function

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

void ambassadorTest() {
    int i;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test1, test2, test3;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting Ambassador Card\n\n");
    printf("\n\n_____TEST 1 - test error condtion when parameters are invalid \n\n");

    memcpy(&test1, &state, sizeof(struct gameState));

    int currentPlayer = whoseTurn(&test1);
    int choice1 = 1; //hand number
    int choice2 = 0; //number to return to supply
    int handPos = 4;

      for (i = 0; i < 5; i++)
    {
      test1.hand[currentPlayer][i] = copper;
    }
    test1.hand[currentPlayer][handPos] = ambassador;
    test1.hand[currentPlayer][1] = mine;

    int ambassadorReturnValue  = ambassadorHandler(&test1, handPos, choice2, currentPlayer, handPos);

    //Check that an estate was not able to be drawn there are none in the pile
    int fail = assert(ambassadorReturnValue, -1);

    if(fail) {
        printf("Failed - expected to get error when player card choice == handpos\n");
    }
    else {
        printf("Passed - got error when player card choice == handpos\n");
    }

        printf("\n\n_____TEST 2 - player cannot return more copies of a card than they possess in their hand \n\n");

        memcpy(&test3, &state, sizeof(struct gameState));

        currentPlayer = whoseTurn(&test3);
        choice1 = 1; //hand number
        choice2 = 2; //number to return to supply
        handPos = 4;

      
          for (i = 0; i < 5; i++)
        {
          test3.hand[currentPlayer][i] = copper;
        }
        test3.hand[currentPlayer][handPos] = ambassador;
        test3.hand[currentPlayer][1] = mine;

        test3.supplyCount[mine] = 6;

        int countOfSupplyMines = test3.supplyCount[mine];
        ambassadorReturnValue  = ambassadorHandler(&test3, choice1, choice2, currentPlayer, handPos);

        //Check that an estate was not able to be drawn there are none in the pile
        fail = assert(test3.supplyCount[mine], countOfSupplyMines - 1);

        if(fail) {
            printf("Failed - player was able to return more cards than they had in their hand\n");
        }
        else {
            printf("Passed - player was not able to return more cards than they possess\n");
        }


        printf("\n\n_____TEST 3 - a player may not recieve a card when they must draw \n\n");

        memcpy(&test2, &state, sizeof(struct gameState));

        currentPlayer = 1;
        choice1 = 1; //hand number
        choice2 = 1; //number to return to supply
        handPos = 4;


          for (i = 0; i < 5; i++)
        {
          test2.hand[1][i] = copper;
        }
        test2.hand[1][handPos] = ambassador;
        test2.hand[1][1] = mine;

        test2.supplyCount[mine] = 6;

        int oppositionPlayerDiscardCount = test2.discardCount[0];
        ambassadorReturnValue  = ambassadorHandler(&test2, choice1, choice2, 1, handPos);

        //Check that an estate was not able to be drawn there are none in the pile
        fail = assert(test2.discardCount[0], oppositionPlayerDiscardCount + 1);

        if(fail) {
            printf("Failed - opposing player should have drawn card\n");
        }
        else {
            printf("Passed - opposiing player drew a card like they should\n");
        }
}

int main(int argc, char *argv[])
{
    ambassadorTest();
    return 0;
}