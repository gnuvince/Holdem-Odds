#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "holdemodds.h"
#include "cards.h"
#include "deck.h"
#include "hands.h"


void usage(const char* name) {
    fprintf(stderr, "Usage: %s <c1> <c2> <c3> <c4>\n", name);
    exit(1);
}


int main(int argc, char **argv) {
    if (argc != 5) {
        usage(argv[0]);
    }

    srand(time(NULL));

    Card deck[48];
    Card cards[4];
    Card hand1[5];
    Card hand2[5];
    size_t results[3] = {0, 0, 0};

    for (size_t i = 0; i < 4; ++i)
        cards[i] = NewCardFromString(argv[1+i]);

    NewDeck(deck, cards, 4);

    for (size_t i = 0; i < 2000000; ++i) {
        DeckShuffle(deck, 3, 48);

        hand1[0] = cards[0];
        hand1[1] = cards[1];
        hand2[0] = cards[2];
        hand2[1] = cards[3];

        for (size_t j = 0; j < 3; ++j) {
            hand1[2 + j] = deck[j];
            hand2[2 + j] = deck[j];
        }

        int c = HandCompare(hand1, hand2);

        if (c > 0) results[0]++;
        else if (c == 0) results[1]++;
        else if (c < 0) results[2]++;
    }

    printf("WIN: %.2f\tTIE: %.2f\tLOSS: %.2f\n",
           results[0] / 2000000.0,
           results[1] / 2000000.0,
           results[2] / 2000000.0);

    return 0;
}
