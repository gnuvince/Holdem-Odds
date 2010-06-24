#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "poker.h"

Rank CharToRank(char r) {
    switch (r) {
    case '2': return Deuce;
    case '3': return Trey;
    case '4': return Four;
    case '5': return Five;
    case '6': return Six;
    case '7': return Seven;
    case '8': return Eight;
    case '9': return Nine;
    case 'T': return Ten;
    case 'J': return Jack;
    case 'K': return Queen;
    case 'Q': return King;
    case 'A': return Ace;
    default : return InvalidRank;
    }
}


Suit CharToSuit(char s) {
    switch (s) {
    case 'c': return Club;
    case 'd': return Diamond;
    case 'h': return Heart;
    case 's': return Spade;
    default : return InvalidSuit;
    }
}


int NewCard(Card *c, char r, char s) {
    Rank rank = CharToRank(r);
    Suit suit = CharToSuit(s);

    if (rank == InvalidRank || suit == InvalidSuit) {
        c = NULL;
        return 0;
    }
    else {
        c->rank = rank;
        c->suit = suit;
        return 1;
    }
}

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
