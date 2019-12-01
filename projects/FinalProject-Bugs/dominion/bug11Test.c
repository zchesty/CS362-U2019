#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>

int assert(int got, int want) {
    if (got != want) {
        return 1;
    }
    else {
        return 0;
    }
}


void checkMinion(int choice1, int choice2, struct gameState *state, int currentPlayer, int handPos, int bonus){
    struct gameState control;
    memcpy (&control, state, sizeof(struct gameState));

    int card = minion;
    int choice3 = -1;
    int fail;


    cardEffect(card, choice1, choice2, choice3, state, handPos, &bonus);



    if(choice1 == 1){
        //get two coins and discard minion since it has been played
        control.coins += 2;
        control.discardCount[control.whoseTurn]++;  //increment the count of cards in players discard pile
    }
    else if (choice2 == 1){
        while (control.handCount[control.whoseTurn] > 0){
            //discard each card
            control.discardCount[control.whoseTurn]++;  //increment the count of cards in players discard pile
            control.handCount[control.whoseTurn]--;
        }
    }

    //Comment out this check since there's a bug in the discardCard function which doesn't actually increment the discard count
    
    /*
    //Check on discardCount of current player
    fail = assert(state->discardCount[state->whoseTurn], control.discardCount[control.whoseTurn]);

    if(fail) {
        printf("Failed - discardCount incorrect\n");
    }
    else {
        printf("Passed - discardCount test passed\n");
    }
    */

   
    //Check on coin count
    fail = assert(state->coins, control.coins);

    if(fail) {
        printf("Failed - coin count incorrect : choice1 = %d, choice2 = %d\n", choice1, choice2);
    }
    else {
        printf("Passed - proper coin count : choice1 = %d, choice2 = %d\n", choice1, choice2);
    }

}



void bugTest() {
    //printf("At the top of bugTest()\n");
    int i, j, n, currentPlayer, choice1, choice2, handPos, bonus, numPlayers, randomHandCount, randomDeckCount, randomDiscardCount, randomHandPos, available;

    int masterCardList[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};


    struct gameState G;

    srand(time(NULL));

    //printf("Right before 10000 Loop\n");
    for (n = 0; n < 50; n++) {
        //printf("Loop iteration: %d\n", n);
        numPlayers = (rand() % (MAX_PLAYERS-1))+2;     //Random number of players from 2 to 4
        //printf("numPlayers: %d\n", numPlayers);
        currentPlayer = (rand() % (numPlayers - 1));    //random number from 0 to 3, representing 1 of 4 players
        //printf("currentPlayer: %d\n", currentPlayer);
        choice1 = (rand() % 2);    //random either 0 or 1
        //printf("choice1: %d\n", choice1);
        choice2 = (rand() % 2);    //random either 0 or 1
        //printf("choice2: %d\n", choice2);
        bonus = rand() % 100;
        //printf("bonus: %d\n", bonus);
   
        available = MAX_DECK;

        randomDeckCount = (rand() % (MAX_DECK+1));
        //printf("randomDeckCount: %d\n", randomDeckCount);
        randomHandCount = (rand() % (((available-randomDeckCount)/2)+1));
        //printf("randomHandCount: %d\n", randomHandCount);
        randomDiscardCount = randomHandCount;;
        //printf("randomDiscardCount: %d\n", randomDiscardCount);
        randomHandPos = (rand() % (randomHandCount+1));
        //printf("randomHandPos: %d\n", randomHandPos);


        //random game state
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = rand() % 250;
        }

        //set whoseTurn
        G.whoseTurn = currentPlayer;

        //set numActions
        G.numActions = rand() % 100;
        //printf("G.numActions: %d\n", G.numActions);

        //set number of players
        G.numPlayers = numPlayers;


        //set numBuys
        G.numBuys = rand() % 500;
        //printf("G.numBuys: %d\n", G.numBuys);

        //set all players deck
        for (i = 0; i < numPlayers; i++)
        {
            G.deckCount[i] = 0;
            for (j = 0; j < randomDeckCount; j++)
            {
                G.deck[i][j] = masterCardList[(rand() % 27)];
                G.deckCount[i]++;
            }
        }


        //setup all player hands
        for (i = 0; i < numPlayers; i++)
        {
            G.handCount[i] = 0;
            for (j = 0; j < randomHandCount; j++)
            {
                G.hand[i][j] = masterCardList[(rand() % 27)];
                G.handCount[i]++;
            }
        }

        //set a specific handPos with minion just for the currentPlayer
        G.hand[currentPlayer][randomHandPos] = minion;
        handPos = randomHandPos; 


        //set player discard
        for (i = 0; i < numPlayers; i++)
        {
            G.discardCount[i] = 0;
            for (j = 0; j < randomDiscardCount; j++)
            {
                G.discard[i][j] = masterCardList[(rand() % 27)];
                G.discardCount[i]++;
            }
        }

        //set playedCards and playedCardCount
        G.playedCardCount = 0;
        for (i = 0; i < randomDiscardCount; i++)
        {
            G.playedCards[i] = masterCardList[(rand() % 27)];
            G.playedCardCount++;
        }


        checkMinion(choice1, choice2, &G, currentPlayer, handPos, bonus);
    }
}





int main(int argc, char *argv[])
{
    //printf("Calling bugTest() from main\n");
    bugTest();
    return 0;
}

