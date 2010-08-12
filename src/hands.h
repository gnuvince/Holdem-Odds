#ifndef _HANDS_H

#define _HANDS_H

#include <stddef.h>
#include <stdbool.h>

#include "cards.h"

#define HAND_LENGTH 5


typedef enum {
    InvalidHand, HighCard, Pair, TwoPair, ThreeOfAKind,
    Straight, Flush, FullHouse, FourOfAKind, StraightFlush,
} HandType;


HandType HandClassify(const Card*);
void     HandSort(Card*);

bool HandIsStraightFlush(const Card*);
bool HandIsFourOfAKind(const Card*);
bool HandIsFullHouse(const Card*);
bool HandIsFlush(const Card*);
bool HandIsStraight(const Card*);
bool HandIsThreeOfAKind(const Card*);
bool HandIsTwoPair(const Card*);
bool HandIsPair(const Card*);
bool HandIsHighCard(const Card*);

int  HandCompare(const Card*, const Card*);

bool HandIsValid(const Card*);

#endif
