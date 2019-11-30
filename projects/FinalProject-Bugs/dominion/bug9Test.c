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
    int i, choice1, choice2, choice3, handPos, bonus, card, fail;
    int seed = 1000;
    int numPlayers = 2;
    struct gameState state, testState;
    int k[10] = {baron, feast, gardens, minion, mine, steward,
            minion, tribute, ambassador, council_room};

    initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting Bug #09\n\n");
    printf("Tribute case incorrectly increases action count by 2\n\n");

    state.whoseTurn = 0;

    // Fill current players hand up with coppers
    for (i = 0; i < 5; i++) {
        state.hand[state.whoseTurn][i] = copper;
    }
    state.handCount[state.whoseTurn] = 5;

    state.discard[0][state.discardCount[0]] = copper;
    state.discardCount[0]++;

    memcpy(&testState, &state, sizeof(struct gameState));

    // params for test
    card = tribute;
    choice1 = -1; 
    choice2 = -1;
    choice3 = -1;
    bonus = 0; 
    handPos = 0;

    //Set last three cards in next player deck to copper
    for(i=0; i<3; i++){
        testState.deck[testState.whoseTurn + 1][testState.deckCount[testState.whoseTurn+1]] = copper; // add Feast to hand
        testState.deckCount[testState.whoseTurn+1]++;
    }

    

    cardEffect(card, choice1, choice2, choice3, &testState, handPos, &bonus);

    //Test that number of actions have not changed. 
    fail = assert(testState.numActions, state.numActions);

    if(fail) {
        printf("Failed - 2 more actions added\n");
    }
    else {
        printf("Passed - Number of actions are appropriate\n");
    }


    //Test that number of coins added is correct
    fail = assert(testState.coins, (state.coins + 2));

    if(fail) {
        printf("Failed - incorrect number of coins\n");
    }
    else {
        printf("Passed - correct number of coins\n");
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
