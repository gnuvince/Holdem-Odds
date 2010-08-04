#include "cards.h"
#include "hands.h"


/*
 * A valid hand has 5 cards in decreasing order.
 */
int HandIsValid(const Card* cards) {
    int ok = 1;

    for (size_t i = 0; i < HAND_LENGTH; ++i)
        ok = ok && CardIsValid(&cards[i]);

    return ok;
}


/*
 * A straight flush is a straight _and_ a flush.
 */
int HandIsStraightFlush(const Card* cards) {
    return HandIsStraight(cards) && HandIsFlush(cards);
}



/*
 * Four of a kind is when 4 of the 5 cards have the same rank.
 */
int HandIsFourOfAKind(const Card* cards) {
    return 0;
}


/*
 * A full house is when a hand is composed of a pair and three of a
 * kind.
 */
int HandIsFullHouse(const Card* cards) {
    return 0;
}


/*
 * A flush is a hand where all cards have the same suit.
 */
int HandIsFlush(const Card* cards) {
    Suit suit = cards[0].suit;

    for (size_t i = 1; i < HAND_LENGTH; ++i)
        if (cards[i].suit != suit)
            return 0;

    return 1;
}


/*
 * A straight is a hand where all cards are successive.  The Ace
 * is considered both high and low, meaning it can follow a King
 * or precede a Deuce.
 */
int HandIsStraight(const Card* cards) {
    return 0;
}


/*
 * A hand is three of a kind if three cards have the same rank
 * and the other two cards don't match.
 */
int HandIsThreeOfAKind(const Card* cards) {
    return 0;
}


/*
 * A hand has two pairs if two sets of two cards share
 * the same rank and the other card doesn't match.
 */
int HandIsTwoPair(const Card* cards) {
    return 0;
}


/*
 * A hand is a pair if two cards share the same rank
 * and the other three cards all have different ranks.
 */
int HandIsPair(const Card* cards) {
    return 0;
}


/*
 * A hand is high card if there is no pair, no straight or
 * no flush.
 */
int HandIsHighCard(const Card* cards) {
    return 0;
}
