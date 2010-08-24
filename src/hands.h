#ifndef _HANDS_H

#define _HANDS_H

#include <stddef.h>
#include <stdbool.h>

#include "cards.h"

#define HAND_LENGTH 5


typedef enum {
    InvalidHand, HighCard, Pair, TwoPair, ThreeOfAKind,
    Wheel, Straight, Flush, FullHouse, FourOfAKind, WheelFlush,
    StraightFlush,
} HandType;


int      HandCompare(Card*, Card*);
HandType HandClassify(Card*);
void     HandSort(Card*);

static bool HandIsStraightFlush(const Card*);
static bool HandIsWheelFlush(const Card*);
static bool HandIsFourOfAKind(const Card*);
static bool HandIsFullHouse(const Card*);
static bool HandIsFlush(const Card*);
static bool HandIsStraight(const Card*);
static bool HandIsWheel(const Card*);
static bool HandIsThreeOfAKind(const Card*);
static bool HandIsTwoPair(const Card*);
static bool HandIsPair(const Card*);
static bool HandIsHighCard(const Card*);

bool HandIsValid(const Card*);

#endif
