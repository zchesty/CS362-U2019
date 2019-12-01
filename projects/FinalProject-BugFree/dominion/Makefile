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


#########

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


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

bug1Test: dominion.o rngs.o bug1Test.c
	gcc -o bug1Test bug1Test.c dominion.o rngs.o $(CFLAGS)

bug2Test: dominion.o rngs.o bug2Test.c
	gcc -o bug2Test bug2Test.c dominion.o rngs.o $(CFLAGS)

bug3Test: dominion.o rngs.o bug3Test.c
	gcc -o bug3Test bug3Test.c dominion.o rngs.o $(CFLAGS)

bug4Test: dominion.o rngs.o bug4Test.c
	gcc -o bug4Test bug4Test.c dominion.o rngs.o $(CFLAGS)

bug5Test: dominion.o rngs.o bug5Test.c
	gcc -o bug5Test bug5Test.c dominion.o rngs.o $(CFLAGS)

bug6Test: dominion.o rngs.o bug6Test.c
	gcc -o bug6Test bug6Test.c dominion.o rngs.o $(CFLAGS)

bug7Test: dominion.o rngs.o bug7Test.c
	gcc -o bug7Test bug7Test.c dominion.o rngs.o $(CFLAGS)

bug8Test: dominion.o rngs.o bug8Test.c
	gcc -o bug8Test bug8Test.c dominion.o rngs.o $(CFLAGS)

bug9Test: dominion.o rngs.o bug9Test.c
	gcc -o bug9Test bug9Test.c dominion.o rngs.o $(CFLAGS)

bug10Test: dominion.o rngs.o bug10Test.c
	gcc -o bug10Test bug10Test.c dominion.o rngs.o $(CFLAGS)

bug11Test: dominion.o rngs.o bug11Test.c
	gcc -o bug11Test bug11Test.c dominion.o rngs.o $(CFLAGS)

unittestresults: bug1Test bug2Test bug3Test bug4Test bug5Test bug6Test bug7Test bug8Test bug9Test bug10Test bug11Test
	./bug1Test &> unittestresults.out
	./bug2Test &> unittestresults.out
	./bug3Test &> unittestresults.out
	./bug4Test &> unittestresults.out
	./bug5Test &> unittestresults.out
	./bug6Test &> unittestresults.out
	./bug7Test &> unittestresults.out
	./bug8Test &> unittestresults.out
	./bug9Test &> unittestresults.out
	./bug10Test &> unittestresults.out
	./bug11Test &> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm bug1Test bug2Test bug3Test bug4Test bug5Test bug6Test bug7Test bug8Test bug9Test bug10Test bug11Test
