CC=clang
#CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2 -std=c99

holdemodds: build
	${CC} ${CFLAGS} src/cards.o src/holdemodds.c -o holdemodds

build: cards.o hands.o
#	${CC} ${CFLAGS} -c src/cards.c -o src/cards.o

clean:
	rm -f holdemodds src/*.o src/tests/*.o src/tests/all_tests


test: build
	${CC} ${CFLAGS} -Isrc -Isrc/tests -o src/tests/all_tests \
		src/cards.o \
		src/hands.o \
		src/tests/all_tests.c \
		src/tests/test_cards.c \
		src/tests/CuTest.c
	src/tests/all_tests

cards.o: src/cards.c src/cards.h
	${CC} ${CFLAGS} -c src/cards.c -o src/cards.o

hands.o: cards.o src/hands.c src/hands.h
	${CC} ${CFLAGS} -c src/hands.c -o src/hands.o
