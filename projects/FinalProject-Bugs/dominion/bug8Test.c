
/*
* Random Test File - One
* Name: Faaiq G Waqar
* Date: November 26th 2019
* Function: Test Bug 8
* Incorrect Bonus Coins Count in Card Effect Function
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
void baronReset(struct gameState *state, int *expectedReturn);
void tributeReset(struct gameState *state, int *expectedReturn);

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
   int i = state->handCount[0];
   int j = state->handCount[0];
   int cardSelector = 0;
   int selectionAmount = rand() % 3;

   state->handCount[0] = i + selectionAmount;

   for(i = j; i < selectionAmount + j; i++){
     cardSelector = rand() % 3;
     switch(cardSelector){
       case 0:
         state->hand[0][i] = copper;
         *expectedReturn += 1;
         break;
       case 1:
         state->hand[0][i] = silver;
         *expectedReturn += 2;
         break;
       case 2:
         state->hand[0][i] = gold;
         *expectedReturn += 3;
         break;
     }
   }
 }

void baronReset(struct gameState *state, int *expectedReturn){
  state->numPlayers = 2;
  state->outpostPlayed = 0;
  state->outpostTurn = 0;
  state->whoseTurn = 0;
  state->phase = 0;
  state->numActions = 0;
  state->coins = 0;
  state->numBuys = 0;

  *expectedReturn = 4;

  state->hand[0][0] = baron;
  state->hand[0][1] = estate;
  state->hand[0][2] = tribute;
  state->hand[0][3] = estate;
  state->hand[0][4] = estate;
  state->handCount[0] = 5;
  state->deck[0][0] = estate;
  state->deck[0][1] = estate;
  state->deck[0][2] = estate;
  state->deck[0][3] = estate;
  state->deck[0][4] = estate;
  state->deck[0][5] = estate;
  state->deckCount[0] = 6;
  state->discardCount[0] = 0;

  state->hand[1][0] = baron;
  state->hand[1][1] = estate;
  state->hand[1][2] = tribute;
  state->hand[1][3] = estate;
  state->hand[1][4] = estate;
  state->handCount[0] = 5;
  state->deck[1][0] = estate;
  state->deck[1][1] = estate;
  state->deck[1][2] = estate;
  state->deck[1][3] = estate;
  state->deck[1][4] = estate;
  state->deck[1][5] = estate;
  state->deckCount[0] = 6;

  state->playedCardCount = 0;

}

void tributeReset(struct gameState *state, int *expectedReturn){
  state->numPlayers = 2;
  state->outpostPlayed = 0;
  state->outpostTurn = 0;
  state->whoseTurn = 0;
  state->phase = 0;
  state->numActions = 0;
  state->coins = 0;
  state->numBuys = 0;

  *expectedReturn = 4;

  state->hand[0][0] = baron;
  state->hand[0][1] = estate;
  state->hand[0][2] = tribute;
  state->hand[0][3] = estate;
  state->hand[0][4] = estate;
  state->handCount[0] = 5;
  state->deck[0][0] = estate;
  state->deck[0][1] = estate;
  state->deck[0][2] = estate;
  state->deck[0][3] = estate;
  state->deck[0][4] = estate;
  state->deck[0][5] = estate;
  state->deckCount[0] = 6;
  state->discardCount[0] = 0;

  state->hand[1][0] = baron;
  state->hand[1][1] = estate;
  state->hand[1][2] = tribute;
  state->hand[1][3] = estate;
  state->hand[1][4] = estate;
  state->handCount[0] = 5;
  state->deck[1][0] = gold;
  state->deck[1][1] = silver;
  state->deck[1][2] = copper;
  state->deck[1][3] = gold;
  state->deck[1][4] = silver;
  state->deck[1][5] = copper;
  state->deckCount[1] = 6;

  state->playedCardCount = 0;
}

 int main(){
   srand(time(NULL));
   int i = 0;
   int functionReturn = 0;
   int expectedReturn = 4;

   int card = baron;
   int choice1 = 1;
   int choice2 = NULL;
   int choice3 = NULL;
   int handPos = 0;
   int bonus = 0;

   struct gameState state;

   printf("BEGIN UNIT TESTING : BUG 8 >> BONUS BUG\n");

   for(i = 0; i < 10; i++){
     printf("Test Baron Iteration %d\n", i+1);
     bonus = 0;
     baronReset(&state, &expectedReturn);
     handInitializer(&state, &expectedReturn);
     functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
     updateCoins(0, &state, bonus);
     bugAssert(state.coins, expectedReturn);
     bugAssert(functionReturn,0);
   }

   card = tribute;

   for(i = 0; i < 10; i++){
     printf("Test Tribute Iteration %d\n", i+1);
     bonus = 0;
     tributeReset(&state, &expectedReturn);
     handInitializer(&state, &expectedReturn);
     functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
     updateCoins(0, &state, bonus);
     bugAssert(state.coins, expectedReturn);
     bugAssert(functionReturn,0);
   }

   printf("END UNIT TESTING : BUG 8 >> BONUS BUG\n");


   return 0;
 }
