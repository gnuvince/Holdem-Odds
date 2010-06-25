OPTIONS=-Wall -O2 -std=c99 -pedantic
CC=clang
#CC=gcc

all:
	make build
	${CC} ${OPTIONS} src/cards.o src/holdemodds.c -o holdemodds

build:
	${CC} ${OPTIONS} -c src/cards.c -o src/cards.o

clean:
	rm -f holdemodds src/*.o
