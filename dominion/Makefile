CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

dominionfix.o: dominion.h dominionfix.c rngs.o
	gcc -c dominionfix.c -g  $(CFLAGS)

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

testFunc.o:
	gcc -c testFunc.c

bugtest1: bugtest1.c dominion.o rngs.o testFunc.o
	gcc -o bugtest1 -g bugtest1.c dominion.o rngs.o testFunc.o $(CFLAGS)
	
bugtest1fix: bugtest1.c dominionfix.o rngs.o testFunc.o
	gcc -o bugtest1fix -g bugtest1.c dominionfix.o rngs.o testFunc.o $(CFLAGS)
	
bugtest2: bugtest2.c dominion.o rngs.o testFunc.o
	gcc -o bugtest2 -g bugtest2.c dominion.o rngs.o testFunc.o $(CFLAGS)

bugtest2fix: bugtest1.c dominionfix.o rngs.o testFunc.o
	gcc -o bugtest2fix -g bugtest2.c dominionfix.o rngs.o testFunc.o $(CFLAGS)
	
bugtest3: bugtest3.c dominion.o rngs.o testFunc.o
	gcc -o bugtest3 -g bugtest3.c dominion.o rngs.o testFunc.o $(CFLAGS)

bugtest3fix: bugtest3.c dominionfix.o rngs.o testFunc.o
	gcc -o bugtest3fix -g bugtest3.c dominionfix.o rngs.o testFunc.o $(CFLAGS)
	
bugtest4: bugtest4.c dominion.o rngs.o testFunc.o
	gcc -o bugtest4 -g bugtest4.c dominion.o rngs.o testFunc.o $(CFLAGS)
    
bugtest4fix: bugtest4.c dominionfix.o rngs.o testFunc.o
	gcc -o bugtest4fix -g bugtest4.c dominionfix.o rngs.o testFunc.o $(CFLAGS)
	
bugtest5: bugtest5.c dominion.o rngs.o testFunc.o
	gcc -o bugtest5 -g bugtest5.c dominion.o rngs.o testFunc.o $(CFLAGS)
    
bugtest5fix: bugtest5.c dominionfix.o rngs.o testFunc.o
	gcc -o bugtest5fix -g bugtest5.c dominionfix.o rngs.o testFunc.o $(CFLAGS)

bugtest6: bugtest6.c dominion.o rngs.o testFunc.o
	gcc -o bugtest6 -g bugtest6.c dominion.o rngs.o testFunc.o $(CFLAGS)
    
bugtest6fix: bugtest6.c dominionfix.o rngs.o testFunc.o
	gcc -o bugtest6fix -g bugtest6.c dominionfix.o rngs.o testFunc.o $(CFLAGS)

bugtest7: bugtest7.c dominion.o rngs.o testFunc.o
	gcc -o bugtest7 -g bugtest7.c dominion.o rngs.o testFunc.o $(CFLAGS)
    
bugtest7fix: bugtest7.c dominionfix.o rngs.o testFunc.o
	gcc -o bugtest7fix -g bugtest7.c dominionfix.o rngs.o testFunc.o $(CFLAGS)

bugtest8: bugtest8.c dominion.o rngs.o testFunc.o
	gcc -o bugtest8 -g bugtest8.c dominion.o rngs.o testFunc.o $(CFLAGS)
    
bugtest8fix: bugtest8.c dominionfix.o rngs.o testFunc.o
	gcc -o bugtest8fix -g bugtest8.c dominionfix.o rngs.o testFunc.o $(CFLAGS)

bugtest9: bugtest9.c dominion.o rngs.o testFunc.o
	gcc -o bugtest9 -g bugtest9.c dominion.o rngs.o testFunc.o $(CFLAGS)
    
bugtest9fix: bugtest9.c dominionfix.o rngs.o testFunc.o
	gcc -o bugtest9fix -g bugtest9.c dominionfix.o rngs.o testFunc.o $(CFLAGS)

bugtest10: bugtest10.c dominion.o rngs.o testFunc.o
	gcc -o bugtest10 -g bugtest10.c dominion.o rngs.o testFunc.o $(CFLAGS)
    
bugtest10fix: bugtest10.c dominionfix.o rngs.o testFunc.o
	gcc -o bugtest10fix -g bugtest10.c dominionfix.o rngs.o testFunc.o $(CFLAGS)
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults: bugtest1 bugtest2 bugtest3 bugtest4 bugtest5 bugtest9 bugtest10
	echo "***** UNIT TEST RESULTS *****" > unittestresults.out
	echo "No tests for bug reports 6, 7, 8 and 11: documentation in PDF" >> unittestresults.out
	./bugtest1 >> unittestresults.out
	./bugtest2 >> unittestresults.out
	./bugtest3 >> unittestresults.out
	./bugtest4 >> unittestresults.out
	./bugtest5 >> unittestresults.out
	./bugtest9 >> unittestresults.out
	./bugtest10 >> unittestresults.out
	echo "***** GCOV BRANCH/FUNCTION COVERAGE RESULTS *****" >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	echo "***** dominion.c.gcov CONTENTS *****" >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
