
/*
* Random Test File - One
* Name: Faaiq G Waqar
* Date: November 26th 2019
* Function: Test Bug 2
* Incorrect Card Comparison for Branch Logic in Mine Card
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
void reInitialize(struct gameState *state);

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

 void reInitialize(struct gameState *state){
   state->numPlayers = 2;
   state->outpostPlayed = 0;
   state->outpostTurn = 0;
   state->whoseTurn = 0;
   state->phase = 0;
   state->numActions = 0;
   state->coins = 0;
   state->numBuys = 0;

   state->hand[0][0] = mine;
   state->hand[0][1] = estate;
   state->hand[0][2] = copper;
   state->hand[0][3] = silver;
   state->hand[0][4] = gold;
   state->handCount[0] = 5;
   state->deck[0][0] = copper;
   state->deck[0][1] = copper;
   state->deck[0][2] = silver;
   state->deck[0][3] = silver;
   state->deck[0][4] = gold;
   state->deck[0][5] = gold;
   state->deckCount[0] = 6;
   state->discardCount[0] = 0;

   state->hand[1][0] = mine;
   state->hand[1][1] = estate;
   state->hand[1][2] = copper;
   state->hand[1][3] = silver;
   state->hand[1][4] = gold;
   state->handCount[0] = 5;
   state->deck[1][0] = copper;
   state->deck[1][1] = copper;
   state->deck[1][2] = silver;
   state->deck[1][3] = silver;
   state->deck[1][4] = gold;
   state->deck[1][5] = gold;
   state->deckCount[0] = 6;

   state->playedCardCount = 0;
   state->supplyCount[copper] = 3;
   state->supplyCount[silver] = 3;
   state->supplyCount[gold] = 3;
   state->supplyCount[mine] = 1;

 }

 int main(){
   int card = mine;
   int choice1 = 2;
   int choice2 = copper;
   int choice3 = NULL;
   int handPos = 0;
   int bonus = 0;
   int functionReturn = 0;

   struct gameState state;

   printf("BEGIN UNIT TESTING : BUG 2 >> MINE CARD BUG\n");
   printf("Unit Test 1: Copper::Copper\n");

   reInitialize(&state);
   functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
   bugAssert(functionReturn, 0);

   printf("Unit Test 2: Copper::Silver\n");

   choice1 = 2;
   choice2 = silver;
   reInitialize(&state);
   functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
   bugAssert(functionReturn, 0);

   printf("Unit Test 3: Copper::Gold\n");

   choice1 = 2;
   choice2 = gold;
   reInitialize(&state);
   functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
   bugAssert(functionReturn, -1);

   printf("Unit Test 4: Silver::Copper\n");

   choice1 = 3;
   choice2 = copper;
   reInitialize(&state);
   functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
   bugAssert(functionReturn, 0);

   printf("Unit Test 5: Silver::Silver\n");

   choice1 = 3;
   choice2 = silver;
   reInitialize(&state);
   functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
   bugAssert(functionReturn, 0);

   printf("Unit Test 6: Silver::Gold\n");

   choice1 = 3;
   choice2 = gold;
   reInitialize(&state);
   functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
   bugAssert(functionReturn, 0);

   printf("Unit Test 7: Gold::Copper\n");

   choice1 = 4;
   choice2 = copper;
   reInitialize(&state);
   functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
   bugAssert(functionReturn, 0);

   printf("Unit Test 8: Gold::Silver\n");

   choice1 = 4;
   choice2 = silver;
   reInitialize(&state);
   functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
   bugAssert(functionReturn, 0);

   printf("Unit Test 9: Gold::Gold\n");

   choice1 = 4;
   choice2 = gold;
   reInitialize(&state);
   functionReturn = cardEffect(card, choice1, choice2, choice3, &state, handPos, &bonus);
   bugAssert(functionReturn, 0);

   printf("END UNIT TESTING : BUG 2 >> MINE CARD BUG\n");

   return 0;
 }
