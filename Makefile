OPTIONS=-Wall -O2 -std=c99 -pedantic
all:
	make build
	gcc ${OPTIONS} src/cards.o src/holdemodds.c -o holdemodds

build:
	gcc ${OPTIONS} -c src/cards.c -o src/cards.o

clean:
	rm -f holdemodds src/*.o
