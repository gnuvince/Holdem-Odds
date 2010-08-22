#include <stdbool.h>
#include <string.h>

#include "bucket.h"
#include "cards.h"
#include "hands.h"


/*
 * Compare two hands and return:
 *   < 0 if hand1 < hand2
 *     0 if hand1 = hand2
 *   > 0 if hand1 > hand2
 */
int HandCompare(const Card* hand1, const Card* hand2) {
    HandType hand1_type = HandClassify(hand1);
    HandType hand2_type = HandClassify(hand2);
    int diff = hand1_type - hand2_type;

    if (diff != 0)
        return diff;

    // Tie breaker when two hands of the same type.

    // Straights and straight flushes are trickier to test for
    // equality because of wheels.  So we have the following
    // procedure:
    //   If both hands are wheels, they are equal (0)
    //   If hand1 is a wheel, hand2 is better (-1)
    //   If hand2 is a wheel, hand1 is better (1)
    if (hand1_type == StraightFlush || hand1_type == Straight) {
        bool hand1_wheel = HandIsWheel(hand1);
        bool hand2_wheel = HandIsWheel(hand2);
        if (hand1_wheel && hand2_wheel)
            return 0;
        if (hand1_wheel)
            return -1;
        if (hand2_wheel)
            return 1;
    }

    // If neither hand is a wheel, find the strongest
    // hand by going one card after the other.  This
    // works for all types of hands when wheels are
    // excluded.
    for (size_t i = 0; i < HAND_LENGTH; ++i) {
        int cmp = CardCompare(&hand1[i], &hand2[i]);
        if (cmp != 0)
            return cmp;
    }
    return 0;
}


/*
 * Sort the cards by the number of cards of the same
 * rank that appear in the hand and then by rank from
 * strongest to weakest.
 */
void HandSort(Card* hand) {
    Bucket buckets[RANKS_PER_DECK];

    // Initialize the count of all buckets to 0 (otherwise,
    // BucketAdd will misbehave).
    for (size_t i = 0; i < RANKS_PER_DECK; ++i)
        buckets[i].count = 0;

    // Copy the cards into the buckets.
    for (size_t i = 0; i < HAND_LENGTH; ++i) {
        size_t bucket_index = hand[i].rank - 1;
        BucketAdd(&buckets[bucket_index], &hand[i]);
    }

    size_t index = 0; // Index of the next card to insert in hand

    // Search for buckets with 4 cards first, then 3, 2 and 1.
    for (size_t count = 4; count > 0; --count) {

        // Go from the highest rank to the lowest rank when inserting into hand
        for (size_t j = RANKS_PER_DECK - 1; j != (size_t)-1; --j) {

            // If the number of cards in the bucket matches the number
            // we're looking for, insert them into the hand.
            if (buckets[j].count == count) {
                memcpy(&hand[index], &buckets[j].cards, sizeof(Card) * count);
                index += count;
            }
        }
    }
}



/*
 * Find the type of the hand that's been given to us.  Go
 * from strongest to weakest type; this assures us that a
 * full house is not classified as merely a pair.
 */
HandType HandClassify(const Card* cards) {
    if (HandIsStraightFlush(cards)) return StraightFlush;
    if (HandIsFourOfAKind(cards))   return FourOfAKind;
    if (HandIsFullHouse(cards))     return FullHouse;
    if (HandIsFlush(cards))         return Flush;
    if (HandIsStraight(cards))      return Straight;
    if (HandIsThreeOfAKind(cards))  return ThreeOfAKind;
    if (HandIsTwoPair(cards))       return TwoPair;
    if (HandIsPair(cards))          return Pair;
    if (HandIsHighCard(cards))      return HighCard;

    return InvalidHand; // Should be unreachable
}


/*
 * A valid hand has 5 cards in decreasing order.
 */
bool HandIsValid(const Card* cards) {
    for (size_t i = 0; i < HAND_LENGTH; ++i)
        if (!CardIsValid(&cards[i]))
            return false;

    return true;
}


/*
 * A straight flush is a straight _and_ a flush.
 */
bool HandIsStraightFlush(const Card* cards) {
    return HandIsStraight(cards) && HandIsFlush(cards);
}



/*
 * Four of a kind is when 4 of the 5 cards have the same rank.
 */
bool HandIsFourOfAKind(const Card* cards) {
    return cards[0].rank == cards[1].rank
        && cards[0].rank == cards[2].rank
        && cards[0].rank == cards[3].rank;
}


/*
 * A full house is when a hand is composed of a pair and three of a
 * kind.
 */
bool HandIsFullHouse(const Card* cards) {
    return cards[0].rank == cards[1].rank
        && cards[0].rank == cards[2].rank
        && cards[3].rank == cards[4].rank;
}


/*
 * A flush is a hand where all cards have the same suit.
 */
bool HandIsFlush(const Card* cards) {
    for (size_t i = 1; i < HAND_LENGTH; ++i)
        if (cards[i].suit != cards[0].suit)
            return false;

    return true;
}


/*
 * A straight is a hand where all cards are successive.  The Ace
 * is considered both high and low, meaning it can follow a King
 * or precede a Deuce.
 */
bool HandIsStraight(const Card* cards) {
    bool isStraight = true;

    // Search for a "normal" straight.
    for (size_t i = 1; i < HAND_LENGTH; ++i) {
        if (cards[i].rank + 1 != cards[i - 1].rank) {
            isStraight = false;
            break;
        }
    }

    if (isStraight)
        return true;

    // If a "normal" straight was not found, test for a wheel.
    return HandIsWheel(cards);
}


/*
 * A wheel is a straight from A to 5
 */
bool HandIsWheel(const Card* cards) {
       return cards[0].rank == Ace
           && cards[1].rank == Five
           && cards[2].rank == Four
           && cards[3].rank == Trey
           && cards[4].rank == Deuce;
}


/*
 * A hand is three of a kind if three cards have the same rank
 * and the other two cards don't match.
 */
bool HandIsThreeOfAKind(const Card* cards) {
    return cards[0].rank == cards[1].rank
        && cards[0].rank == cards[2].rank;
}


/*
 * A hand has two pairs if two sets of two cards share
 * the same rank and the other card doesn't match.
 */
bool HandIsTwoPair(const Card* cards) {
    return cards[0].rank == cards[1].rank
        && cards[2].rank == cards[3].rank;
}


/*
 * A hand is a pair if two cards share the same rank
 * and the other three cards all have different ranks.
 */
bool HandIsPair(const Card* cards) {
    return cards[0].rank == cards[1].rank;
}


/*
 * A hand is high card if there is no pair, no straight or
 * no flush.  (Any hand is a high card hand)
 */
bool HandIsHighCard(const Card* cards) {
    (void)cards;
    return true;
}
