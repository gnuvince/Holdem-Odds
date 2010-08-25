CC=clang
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2 -std=c99 -g -pg

holdemodds: build
	${CC} ${CFLAGS} \
		src/cards.o \
		src/hands.o \
		src/deck.o  \
		src/bucket.o \
		src/holdemodds.c -o holdemodds

build: cards.o hands.o bucket.o deck.o

clean:
	rm -f holdemodds src/*.o src/tests/*.o src/tests/all_tests


test: build
	${CC} ${CFLAGS} -Isrc -Isrc/tests -o src/tests/all_tests \
		src/cards.o \
		src/hands.o \
		src/bucket.o \
		src/deck.o \
		src/tests/all_tests.c \
		src/tests/test_cards.c \
		src/tests/test_hands.c \
		src/tests/test_bucket.c \
		src/tests/test_deck.c \
		src/tests/CuTest.c
	src/tests/all_tests

cards.o: src/cards.c src/cards.h
	${CC} ${CFLAGS} -c src/cards.c -o src/cards.o

hands.o: cards.o src/hands.c src/hands.h
	${CC} ${CFLAGS} -c src/hands.c -o src/hands.o

bucket.o: cards.o src/bucket.c src/bucket.h
	${CC} ${CFLAGS} -c src/bucket.c -o src/bucket.o

deck.o: cards.o src/deck.c src/deck.h
	${CC} ${CFLAGS} -c src/deck.c -o src/deck.o
