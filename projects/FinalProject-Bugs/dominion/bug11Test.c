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

    int controlBonus = bonus;
    int card = minion;
    int choice3 = -1;
    int fail;


    cardEffect(card, choice1, choice2, choice3, &testState, handPos, &bonus);



    if(choice1 == 1){
        //get two coins and discard minion since it has been played
        controlBonus += 2;

        control.discard[currentPlayer][control.discardCount[currentPlayer]] = control.hand[currentPlayer][handPos];
        control.discardCount[currentPlayer]++;  //increment the count of cards in players discard pile

        control.hand[currentPlayer][handPos] = -1;
        control.hand[currentPlayer][handPos] = control.hand[currentPlayer][ (control.handCount[currentPlayer] - 1)];
        control.hand[currentPlayer][control.handCount[currentPlayer] - 1] = -1;
        control.handCount[currentPlayer]--;
    }
    else if (choice2 == 1){
        while (control.handCount[currentPlayer] > 0){
            //discard each card
            control.discard[currentPlayer][control.discardCount[currentPlayer]] = control.hand[currentPlayer][0];
            control.discardCount[currentPlayer]++;  //increment the count of cards in players discard pile
            control.hand[currentPlayer][0] = -1;
            control.hand[currentPlayer][0] = control.hand[currentPlayer][ (control.handCount[currentPlayer] - 1)];
            control.hand[currentPlayer][control.handCount[currentPlayer] - 1] = -1;
            control.handCount[currentPlayer]--;
        }
        //draw 4 cards for current player
        for(int x = 0; x < 4; x++){
            //assume there are enough cards in player's deck
            control.hand[currentPlayer][control.handCount[currentPlayer]] = control.deck[currentPlayer][control.deckCount[currentPlayer] - 1];//Add card to end of hand
            control.deckCount[currentPlayer]--;  //Decrement deck count
            control.handCount[currentPlayer]++;  //Increment hand count
        }



        //other players discard hand and redraw if hand size > 4
        for (int otherPlayer = 0; otherPlayer < control.numPlayers; otherPlayer++)
        {
            if (otherPlayer != currentPlayer)
            {
                //otherPlayer = 0 is current player. skip current player in this portion since we already did it above
                if ( control.handCount[otherPlayer] > 4 )
                {
                    //discard hand
                    while( control.handCount[otherPlayer] > 0 )
                    {
                        control.discard[otherPlayer][control.discardCount[otherPlayer]] = control.hand[otherPlayer][0];
                        control.discardCount[otherPlayer]++;  //increment the count of cards in players discard pile
                        control.hand[otherPlayer][0] = -1;
                        control.hand[otherPlayer][0] = control.hand[otherPlayer][ (control.handCount[otherPlayer] - 1)];
                        control.hand[otherPlayer][control.handCount[otherPlayer] - 1] = -1;
                        control.handCount[otherPlayer]--;
                    }

                    //draw 4
                    for (int j = 0; j < 4; j++)
                    {
                        //assume there are enough cards in player's deck
                        control.hand[otherPlayer][control.handCount[otherPlayer]] = control.deck[otherPlayer][control.deckCount[otherPlayer] - 1];//Add card to end of hand
                        control.deckCount[otherPlayer]--;  //Decrement deck count
                        control.handCount[otherPlayer]++;  //Increment hand count
                    }
                }
            }
        }
    }


    //Check on discardCount of current player
    fail = assert(state->discardCount[state->whoseTurn], control.discardCount[control.whoseTurn]);

    if(fail) {
        printf("Failed - discardCount incorrect\n");
    }
    else {
        printf("Passed - discardCount test passed\n");
    }


    //Check on coin count
    fail = assert(state->coins, control.coins);

    if(fail) {
        printf("Failed - coin count incorrect\n");
    }
    else {
        printf("Passed - proper coin count\n");
    }

}



void bugTest() {
    int i, j, n, currentPlayer, choice1, choice2, handPos, bonus, numPlayers, randomHandCount, randomDeckCount, randomDiscardCount, randomHandPos;

    int masterCardList[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};


    struct gameState G;

    srand(time(NULL));

    for (n = 0; n < 100; n++) {
        numPlayers = (rand() % (MAX_PLAYERS-1))+2;     //Random number of players from 2 to 4
        currentPlayer = (rand() % (numPlayers - 1));    //random number from 0 to 3, representing 1 of 4 players
        choice1 = (rand() % 2);    //random either 0 or 1
        choice2 = (rand() % 2);    //random either 0 or 1
        bonus = rand() % 100;
        randomDeckCount = (rand() % (MAX_DECK+1));
        randomHandCount = (rand() % (MAX_HAND+1));
        randomDiscardCount = randomDeckCount - (rand() % ((MAX_DECK/2)+1));
        randomHandPos = (rand() % randomHandCount+1);

        //random game state
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = rand() % 250;
        }

        //set whoseTurn
        G.whoseTurn = currentPlayer;

        //set numActions
        G.numActions = rand() % 100;

        //set number of players
        G.numPlayers = numPlayers;


        //set numBuys
        G.numBuys = rand() % 500;

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


        checkMinion(choice1, choice2, &G, currentPlayer, handPos, bonus);
    }
}





int main(int argc, char *argv[])
{
    bugTest();
    return 0;
}

