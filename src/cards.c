#include <stdlib.h>

#include "cards.h"


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
    return (Rank)indexOf(r, RANK_CHARS, RANKS_PER_DECK);
}


Suit CharToSuit(char s) {
    return (Suit)indexOf(s, SUIT_CHARS, SUITS_PER_DECK);
}


/*
 * Create a new card and return 1 if the operation
 * was successful, 0 otherwise.
 */
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
    if (a == NULL)
        return 1;
    if (b == NULL)
        return -1;
    return a->rank - b->rank;
}


void CardToString(char* out, const Card* c) {
    if (c == NULL || c->rank == InvalidRank || c->suit == InvalidSuit) {
        out[0] = '-';
        out[1] = '-';
    }
    else {
        out[0] = RANK_CHARS[(int)c->rank - 1];
        out[1] = SUIT_CHARS[(int)c->suit - 1];
    }
    out[2] = '\0';
}
