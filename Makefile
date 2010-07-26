CC=clang
#CC=gcc
CFLAGS=-Wall -O2 -std=c99 -pedantic

holdemodds: build
	${CC} ${CFLAGS} src/cards.o src/holdemodds.c -o holdemodds

build:
	${CC} ${CFLAGS} -c src/cards.c -o src/cards.o

clean:
	rm -f holdemodds src/*.o src/tests/*.o src/tests/all_tests


test: build
	${CC} ${CFLAGS} -Isrc -Isrc/tests -o src/tests/all_tests \
		src/cards.o \
		src/tests/all_tests.c \
		src/tests/test_cards.c \
		src/tests/CuTest.c
	src/tests/all_tests
