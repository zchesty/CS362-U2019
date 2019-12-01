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
    int i, choice1, choice2, choice3, handPos, bonus, card, returnVal, fail;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, testState;
	int k[10] = {baron, remodel, gardens, minion, mine, steward,
			minion, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting Bug #03\n\n");
    printf("Remodel case returns -1 for valid choice1 and choice2 inputs\n\n");

    state.whoseTurn = 0;

	// Fill current players hand up with coppers
	for (i = 0; i < 5; i++) {
		state.hand[state.whoseTurn][i] = copper;
	}


    /******************************************************************************
     * Positive Test Case
    ******************************************************************************/

    memcpy(&testState, &state, sizeof(struct gameState));

	// params for test
	card = remodel;
    choice1 = 1; 
    choice2 = minion;
    choice3 = 0;
    bonus = 0; 
    handPos = 0;

	testState.hand[testState.whoseTurn][handPos] = remodel; // add Remodel to hand
	testState.hand[testState.whoseTurn][choice1] = gardens; // add choice1 card to hand

    returnVal = cardEffect(card, choice1, choice2, choice3, &testState, handPos, &bonus);

    //Test that the return value of cardEffect is what we expect
    fail = assert(returnVal, 0);

    if(fail) {
        printf("Failed - return value is -1, expected is 0\n");
    }
    else {
        printf("Passed - return value is 0, expected is 0\n");
    }





    /******************************************************************************
     * Negative Test Case
    ******************************************************************************/

    memcpy(&testState, &state, sizeof(struct gameState));

	// params for test
	card = remodel;
    choice1 = 1; 
    choice2 = gold;
    choice3 = 0;
    bonus = 0; 
    handPos = 0;

	testState.hand[testState.whoseTurn][handPos] = remodel; // add Remodel to hand
	testState.hand[testState.whoseTurn][choice1] = silver; // add choice1 card to hand

    returnVal = cardEffect(card, choice1, choice2, choice3, &testState, handPos, &bonus);

    //Test that the return value of cardEffect is what we expect
    fail = assert(returnVal, -1);

    if(fail) {
        printf("Failed - return value is 0, expected is -1\n");
    }
    else {
        printf("Passed - return value is -1, expected is -1\n");
    }
}




/******************************************************************************
 * Main
******************************************************************************/


int main(int argc, char *argv[])
{
    bugTest();
    return 0;
}


