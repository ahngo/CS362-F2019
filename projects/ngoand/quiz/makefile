CFLAGS= -Wall -fpic -coverage -lm -std=c99
PROGRAM= testme
.PHONY: all run

all: run
	
run:    $(PROGRAM)
	./$(PROGRAM)

testme:
	gcc -o testme testme.c $(CFLAGS)