all:
	gcc -Wall -O2 -std=c99 -pedantic src/poker.c -o poker

clean:
	rm -f poker
