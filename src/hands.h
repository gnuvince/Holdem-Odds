#ifndef _HANDS_H

#define _HANDS_H

#include "cards.h"

#define HAND_LENGTH 5


typedef enum {
    InvalidHand, HighCard, Pair, TwoPair, ThreeOfAKind,
    Straight, Flush, FullHouse, FourOfAKind, StraightFlush,
} HandType;


typedef struct {
    HandType type;
    Card* extraInformation;
} HandClass;


int HandIsStraightFlush(const Card*);
int HandIsFourOfAKind(const Card*);
int HandIsFullHouse(const Card*);
int HandIsFlush(const Card*);
int HandIsStraight(const Card*);
int HandIsThreeOfAKind(const Card*);
int HandIsTwoPair(const Card*);
int HandIsPair(const Card*);
int HandIsHighCard(const Card*);

HandType HandClassify(const Card*);

int HandIsValid(const Card*);

#endif
