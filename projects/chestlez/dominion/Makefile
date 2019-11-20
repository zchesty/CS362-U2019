CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

baronTestUnit: dominion.o rngs.o unittest1.c
	gcc -o baronTestUnit unittest1.c dominion.o rngs.o $(CFLAGS)

minionTestUnit: dominion.o rngs.o unittest2.c
	gcc -o minionTestUnit unittest2.c dominion.o rngs.o $(CFLAGS)

ambassadorTestUnit: dominion.o rngs.o unittest3.c
	gcc -o ambassadorTestUnit unittest3.c dominion.o rngs.o $(CFLAGS)

tributeTestUnit: dominion.o rngs.o unittest4.c
	gcc -o tributeTestUnit unittest4.c dominion.o rngs.o $(CFLAGS)

mineTestUnit: dominion.o rngs.o unittest5.c
	gcc -o mineTestUnit unittest5.c dominion.o rngs.o $(CFLAGS)

baronTestRandom: dominion.o rngs.o randomtestcard1.c
	gcc -o baronTestRandom randomtestcard1.c dominion.o rngs.o $(CFLAGS)

minionTestRandom: dominion.o rngs.o randomtestcard2.c
	gcc -o minionTestRandom randomtestcard2.c dominion.o rngs.o $(CFLAGS)

tributeTestRandom: dominion.o rngs.o randomtestcard3.c
	gcc -o tributeTestRandom randomtestcard3.c dominion.o rngs.o $(CFLAGS)

randomtestresults: baronTestRandom minionTestRandom tributeTestRandom
	./baronTestRandom &> randomtestresults.out
	./minionTestRandom >> randomtestresults.out
	./tributeTestRandom >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out

unittestresults: baronTestUnit minionTestUnit ambassadorTestUnit tributeTestUnit mineTestUnit
	./baronTestUnit &> unittestresults.out
	./minionTestUnit >> unittestresults.out
	./ambassadorTestUnit >> unittestresults.out
	./tributeTestUnit >> unittestresults.out
	./mineTestUnit >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 




clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe baronTestRandom minionTestRandom tributeTestRandom minionTestUnit baronTestUnit tributeTestUnit mineTestUnit ambassadorTestUnit
