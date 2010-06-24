all:
	gcc -Wall -O2 -std=c99 -pedantic -c src/cards.c -o src/cards.o
	gcc -Wall -O2 -std=c99 -pedantic src/cards.o src/holdemodds.c -o holdemodds

clean:
	rm -f holdemodds src/*.o
