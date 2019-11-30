
/*
* Random Test File - One
* Name: Faaiq G Waqar
* Date: November 26th 2019
* Function: Test Bug 5
* Incorrect Card Count Used in scoring function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int bugAssert(int, int);
void handInitializer(struct gameState *state, int *expectedReturn);
void discardInitializer(struct gameState *state, int *expectedReturn);
void deckInitializer(struct gameState *state, int *expectedReturn);
void callInitializer(struct gameState *state, int *expectedReturn);
void resetModule(struct gameState *state, int *expectedReturn);

int bugAssert(int variable1, int variable2){
// Context Here: Variable 1 is our Actual, Variable 2 is Expectation
 if(variable1 == variable2){
	 printf("PASSED: Equivalent to Expectation\n");
	 return 0;
 }
 if(variable1 > variable2){
	 printf("FAILED: Greater Than Expectation\n");
	 return -1;
 }
 if(variable1 < variable2){
	 printf("FAILED: Less Than Expectation\n");
	 return 1;
 }

  return 0;
 }

void handInitializer(struct gameState *state, int *expectedReturn){
  int i = 0;
  int cardSelector = 0;
  int selectionAmount = rand() % 6;

  state->handCount[0] = selectionAmount;

  for(i = 0; i < selectionAmount; i++){
    cardSelector = rand() % 5;
    switch(cardSelector){
      case 0:
        state->hand[0][i] = curse;
        *expectedReturn -= 1;
        break;
      case 1:
        state->hand[0][i] = estate;
        *expectedReturn += 1;
        break;
      case 2:
        state->hand[0][i] = duchy;
        *expectedReturn += 3;
        break;
      case 3:
        state->hand[0][i] = province;
        *expectedReturn += 6;
        break;
      case 4:
        state->hand[0][i] = great_hall;
        *expectedReturn += 1;
        break;
    }
  }
}

void discardInitializer(struct gameState *state, int *expectedReturn){
  int i = 0;
  int cardSelector = 0;
  int selectionAmount = rand() % 6;

  state->discardCount[0] = selectionAmount;

  for(i = 0; i < selectionAmount; i++){
    cardSelector = rand() % 5;
    switch(cardSelector){
      case 0:
        state->discard[0][i] = curse;
        *expectedReturn -= 1;
        break;
      case 1:
        state->discard[0][i] = estate;
        *expectedReturn += 1;
        break;
      case 2:
        state->discard[0][i] = duchy;
        *expectedReturn += 3;
        break;
      case 3:
        state->discard[0][i] = province;
        *expectedReturn += 6;
        break;
      case 4:
        state->discard[0][i] = great_hall;
        *expectedReturn += 1;
        break;
    }
  }
}

void deckInitializer(struct gameState *state, int *expectedReturn){
  int i = 0;
  int cardSelector = 0;
  int selectionAmount = rand() % 6;

  state->deckCount[0] = selectionAmount;

  for(i = 0; i < selectionAmount; i++){
    cardSelector = rand() % 5;
    switch(cardSelector){
      case 0:
        state->deck[0][i] = curse;
        *expectedReturn -= 1;
        break;
      case 1:
        state->deck[0][i] = estate;
        *expectedReturn += 1;
        break;
      case 2:
        state->deck[0][i] = duchy;
        *expectedReturn += 3;
        break;
      case 3:
        state->deck[0][i] = province;
        *expectedReturn += 6;
        break;
      case 4:
        state->deck[0][i] = great_hall;
        *expectedReturn += 1;
        break;
    }
  }
}

void callInitializer(struct gameState *state, int *expectedReturn){
  handInitializer(state, expectedReturn);
  discardInitializer(state, expectedReturn);
  deckInitializer(state, expectedReturn);
}

void resetModule(struct gameState *state, int *expectedReturn){
  *expectedReturn = 0;
  state->deckCount[0] = 0;
  state->discardCount[0] = 0;
  state->handCount[0] = 0;
}

int main(){
   srand(time(NULL));
   int player = 0;
   int i = 0;
   int functionReturn = 0;
   int expectedReturn = 0;

   struct gameState state;

   printf("BEGIN UNIT TESTING : BUG 5 >> SCOREFOR BUG\n");

   for(i = 0; i < 25; i++){
     printf("Test Iteration %d\n", i+1);
     resetModule(&state, &expectedReturn);
     callInitializer(&state, &expectedReturn);
     functionReturn = scoreFor(player, &state);
     bugAssert(functionReturn, expectedReturn);
   }

   printf("END UNIT TESTING : BUG 5 >> SCOREFOR BUG\n");

   return 0;
}
