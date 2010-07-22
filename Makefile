CC=clang
#CC=gcc
OPTIONS=-Wall -O2 -std=c99 -pedantic

all:
	make build
	${CC} ${OPTIONS} src/cards.o src/holdemodds.c -o holdemodds

build:
	${CC} ${OPTIONS} -c src/cards.c -o src/cards.o

clean:
	rm -f holdemodds src/*.o src/tests/*.o src/tests/all_tests


test:
	make build
	${CC} ${OPTIONS} -Isrc -Isrc/tests -o src/tests/all_tests \
		src/cards.o \
		src/tests/all_tests.c \
		src/tests/test_cards.c \
		src/tests/CuTest.c
	src/tests/all_tests
