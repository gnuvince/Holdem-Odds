#include <stdlib.h>

#include "cards.h"

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


int CompareCards(const Card* a, const Card* b) {
    return b->rank - a->rank;
}
