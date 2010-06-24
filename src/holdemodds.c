#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cards.h"



void usage(char* name) {
    fprintf(stderr, "Usage: %s <spec>\n", name);
    exit(1);
}



int main(int argc, char **argv) {
    Card card;

    if (argc == 1 || strlen(argv[1]) != 2) {
        usage(argv[0]);
    }

    char rankSpec = argv[1][0];
    char suitSpec = argv[1][1];

    if (NewCard(&card, rankSpec, suitSpec)) {
        printf("We have a card!\n");
    }
    else {
        printf("This card is invalid...\n");
    }

    return 0;
}
