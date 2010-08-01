#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "holdemodds.h"
#include "cards.h"



void usage(const char* name) {
    fprintf(stderr, "Usage: %s <spec1> <spec2>\n", name);
    exit(1);
}


int main(int argc, char **argv) {
    if (argc != 3) {
        usage(argv[0]);
    }

    Card card1 = NewCardFromString(argv[1]);
    Card card2 = NewCardFromString(argv[2]);

    char card1Str[3];
    char card2Str[3];

    if (CardIsValid(&card1) && CardIsValid(&card2)) {
        char relation;
        int comp = CardCompare(&card1, &card2);
        if (comp < 0)
            relation = '<';
        else if (comp > 0)
            relation = '>';
        else
            relation = '=';

        CardToString(card1Str, &card1);
        CardToString(card2Str, &card2);
        printf("%s %c %s\n", card1Str, relation, card2Str);
    }
    else {
        usage(argv[0]);
    }

    return 0;
}
