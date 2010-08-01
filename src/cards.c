#include <stdlib.h>
#include <string.h>

#include "cards.h"


Card INVALID_CARD = { .rank = InvalidRank, .suit = InvalidSuit };


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
 * Create a new card and return it.  rank and suit are set
 * to InvalidRank and InvalidSuit respectively if the
 * parameters are invalid.
 */
Card NewCard(Rank rank, Suit suit) {
    Card card = { .rank = rank, .suit = suit };

    if (CardIsValid(&card))
        return card;
    else
        return INVALID_CARD;
}


Card NewCardFromChars(char r, char s) {
    Rank rank = CharToRank(r);
    Suit suit = CharToSuit(s);

    return NewCard(rank, suit);
}


Card NewCardFromString(char *s) {
    if (strlen(s) != 2)
        return INVALID_CARD;
    else
        return NewCardFromChars(s[0], s[1]);
}


int CardCompare(const Card* a, const Card* b) {
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


int CardIsValid(Card* c) {
    return (c->rank >= Deuce && c->rank <= Ace &&
            c->suit >= Club  && c->suit <= Spade);
}
