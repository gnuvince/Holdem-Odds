all:
	gcc -Wall -O2 -std=c99 -pedantic poker.c -o poker

clean:
	rm -f poker
