// This file contains the unit test for the tribute handler function

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

void tributeTest() {
	int seed = 1000;
	int numPlayers = 2;
	struct gameState state, test1, test2, test3, test4, test5;
	int k[10] = {baron, feast, gardens, minion, mine, steward,
			sea_hag, tribute, ambassador, council_room};

	initializeGame(numPlayers, k, seed, &state);

    printf("\nTesting tribute Card\n\n");
    printf("\n\n_____TEST 1 - opposing player only has 1 card in deck to display should gain 2 coins and nothing else \n\n");

    memcpy(&test1, &state, sizeof(struct gameState));

    int currentPlayer = whoseTurn(&test1);
    int opposingPlayer = 1;

    test1.discardCount[opposingPlayer] = 0;
    test1.deckCount[opposingPlayer] = 1;

    test1.deck[opposingPlayer][0] = copper;

    tributeCardEffect(opposingPlayer, currentPlayer, &test1);

    int fail = assert(test1.coins, state.coins + 2);

    if(fail) {
        printf("Failed - player should gain 2 coins\n");
    }
    else {
        printf("Passed - player gains 2 coins\n");
    }
    fail = assert(test1.numActions, state.numActions);

    if(fail) {
            printf("Failed - player should not have gained any actions\n");
        }
        else {
            printf("Passed - player did not gain any actions\n");
        }

    fail = assert(test1.handCount[currentPlayer], state.handCount[currentPlayer]);

        if(fail) {
                printf("Failed - player should not have gained any cards\n");
            }
            else {
                printf("Passed - player did not gain any cards\n");
            }

    printf("\n\n_____TEST 2 - opposing player only has a garden to show and a copper, should gain 2 coins and 2 cards no actions \n\n");

    memcpy(&test2, &state, sizeof(struct gameState));

    currentPlayer = whoseTurn(&test2);
    opposingPlayer = 1;

    test2.discardCount[opposingPlayer] = 0;
    test2.deckCount[opposingPlayer] = 2;



    test2.deck[opposingPlayer][0] = copper;
    test2.deck[opposingPlayer][1] = estate;

    tributeCardEffect(opposingPlayer, currentPlayer, &test2);

    fail = assert(test2.coins, state.coins + 2);

    if(fail) {
        printf("Failed - player should gain 2 coins\n");
    }
    else {
        printf("Passed - player gains 2 coins\n");
    }
    fail = assert(test2.numActions, state.numActions);

    if(fail) {
            printf("Failed - player should not have gained any actions\n");
        }
        else {
            printf("Passed - player did not gain any actions\n");
        }

    fail = assert(test2.handCount[currentPlayer], state.handCount[currentPlayer] + 2);

        if(fail) {
                printf("Failed - player should have gained 2 cards\n");
            }
            else {
                printf("Passed - player did gain 2 cards\n");
            }

    printf("\n\n_____TEST 3 - duplicate cards are draw from opposing player with a shuffle\n\n");

    memcpy(&test3, &state, sizeof(struct gameState));

    currentPlayer = whoseTurn(&test3);
    opposingPlayer = 1;

    test3.discardCount[opposingPlayer] = 2;
    test3.deckCount[opposingPlayer] = 0;

    test3.discard[opposingPlayer][0] = mine;
    test3.discard[opposingPlayer][1] = mine;

    tributeCardEffect(opposingPlayer, currentPlayer, &test3);

    fail = assert(test3.coins, state.coins);

    if(fail) {
        printf("Failed - player should not gain any coins\n");
    }
    else {
        printf("Passed - player gains no coins\n");
    }
    fail = assert(test3.numActions, state.numActions + 2);

    if(fail) {
            printf("Failed - player should have gained 2 actions\n");
        }
        else {
            printf("Passed - player did not gain the correct amount of actions\n");
        }

    fail = assert(test3.handCount[currentPlayer], state.handCount[currentPlayer]);

        if(fail) {
                printf("Failed - player should not have gained cards\n");
            }
            else {
                printf("Passed - player gains no cards\n");
            }
printf("\n\n_____TEST 4 - opposing player has no cards to show\n\n");

    memcpy(&test4, &state, sizeof(struct gameState));

    currentPlayer = whoseTurn(&test4);
    opposingPlayer = 1;

    test4.discardCount[opposingPlayer] = 0;
    test4.deckCount[opposingPlayer] = 0;


    tributeCardEffect(opposingPlayer, currentPlayer, &test4);

    fail = assert(test4.coins, state.coins);

    if(fail) {
        printf("Failed - player should gain no coins\n");
    }
    else {
        printf("Passed - player gains no coins\n");
    }
    fail = assert(test4.numActions, state.numActions);

    if(fail) {
            printf("Failed - player should not have gained any actions\n");
        }
        else {
            printf("Passed - player did not gain any actions\n");
        }

    fail = assert(test4.handCount[currentPlayer], state.handCount[currentPlayer] + 2);

        if(fail) {
                printf("Failed - player should not gain cards\n");
            }
            else {
                printf("Passed - player gains no cards\n");
            }
    
    printf("\n\n_____TEST 5 - opposing player only has 1 card in deck to display should gain 2 coins and nothing else \n\n");
    
        memcpy(&test5, &state, sizeof(struct gameState));
    
        currentPlayer = whoseTurn(&test5);
        opposingPlayer = 1;
    
        test5.discardCount[opposingPlayer] = 1;
        test5.deckCount[opposingPlayer] = 0;
    
        test5.discard[opposingPlayer][0] = copper;
    
        tributeCardEffect(opposingPlayer, currentPlayer, &test5);
    
        fail = assert(test5.coins, state.coins + 2);
    
        if(fail) {
            printf("Failed - player should gain 2 coins\n");
        }
        else {
            printf("Passed - player gains 2 coins\n");
        }
        fail = assert(test5.numActions, state.numActions);
    
        if(fail) {
                printf("Failed - player should not have gained any actions\n");
            }
            else {
                printf("Passed - player did not gain any actions\n");
            }
    
        fail = assert(test5.handCount[currentPlayer], state.handCount[currentPlayer]);
    
            if(fail) {
                    printf("Failed - player should not have gained any cards\n");
                }
                else {
                    printf("Passed - player did not gain any cards\n");
                }

}


int main(int argc, char *argv[])
{
    tributeTest();
    return 0;
}