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

    state.discard[0][state.discardCount[0]] = copper;
    state.discardCount[0]++;

    memcpy(&testState, &state, sizeof(struct gameState));

    // params for test
    card = feast;
    choice1 = province; 
    choice2 = 0;
    choice3 = 0;
    bonus = 0; 
    handPos = 0;

    testState.hand[testState.whoseTurn][handPos] = feast; // add Remodel to hand

    returnVal = cardEffect(card, choice1, choice2, choice3, &testState, handPos, &bonus);

    //Test that the return value of cardEffect is what we expect
    fail = assert(testState.discard[0][testState.discardCount[0]-1], state.discard[0][state.discardCount[0]-1]);

    if(fail) {
        printf("Failed - Province added to discard pile when it should not have been\n");
    }
    else {
        printf("Passed - Province not added to discard pile\n");
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
