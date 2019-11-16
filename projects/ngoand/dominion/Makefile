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

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o testFunc.o
	gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	
unittest1: unittest1.c dominion.o rngs.o testFunc.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o testFunc.o $(CFLAGS)
	
unittest2: unittest2.c dominion.o rngs.o testFunc.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o testFunc.o $(CFLAGS)
	
unittest3: unittest3.c dominion.o rngs.o testFunc.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o testFunc.o $(CFLAGS)
	
unittest4: unittest4.c dominion.o rngs.o testFunc.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o testFunc.o $(CFLAGS)
	
unittest5: unittest5.c dominion.o rngs.o testFunc.o
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o testFunc.o $(CFLAGS)
	
unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5
	echo "***** UNIT TEST RESULTS *****" > unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./unittest5 >> unittestresults.out
	echo "***** GCOV BRANCH/FUNCTION COVERAGE RESULTS *****" >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	echo "***** dominion.c.gcov CONTENTS *****" >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

testFunc.o:
	gcc -c testFunc.c

randomtestcard1: randomtestcard1.c dominion.o rngs.o testFunc.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o testFunc.o $(CFLAGS)
	
randomtestcard2: randomtestcard2.c dominion.o rngs.o testFunc.o
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o testFunc.o $(CFLAGS)
	
randomtestcard3: randomtestcard3.c dominion.o rngs.o testFunc.o
	gcc -o randomtestcard3 randomtestcard3.c dominion.o rngs.o testFunc.o $(CFLAGS)

randomtestresults: randomtestcard1 randomtestcard2 randomtestcard3
	echo "***** RANDOM TEST RESULTS *****" > randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	echo "***** BARON TEST CONCLUDED *****" >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out 
	echo "***** MINION TEST CONCLUDED *****" >> randomtestresults.out
	./randomtestcard3 >> randomtestresults.out
	echo "***** TRIBUTE TEST CONCLUDED *****" >> randomtestresults.out
	echo "***** GCOV BRANCH/FUNCTION COVERAGE RESULTS *****" >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
	echo "***** dominion.c.gcov CONTENTS *****" >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
