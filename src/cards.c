#include <stdlib.h>

#include "cards.h"


char RankChars[RANKS_PER_DECK] = "23456789TJQKA";
char SuitChars[SUITS_PER_DECK] = "cdhs";


/*
 * Return the 1-based index of c in chars.  Return
 * 0 if the character isn't found.
 */
size_t indexOf(char c, const char* chars, size_t N) {
    for (size_t i = 0; i < N; ++i) {
        if (chars[i] == c) {
            return i+1;
        }
    }
    return 0;
}

Rank CharToRank(char r) {
    return indexOf(r, RankChars, RANKS_PER_DECK);
}


Suit CharToSuit(char s) {
    return indexOf(s, SuitChars, SUITS_PER_DECK);
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


int CompareCards(const Card* a, const Card* b) {
    return b->rank - a->rank;
}
