#include <stdio.h>
#include <string.h>

#include "CuTest.h"
#include "cards.h"
#include "hands.h"

#define OUTPUT_LENGTH 512 // Error messages should not exceed this length.

static char ranks[] = " 23456789TJQKA";
static char suits[] = " chds";
static size_t ranksLength = 13;
static size_t suitsLength = 4;


void NewHandFromString(const char* string, Card* hand) {
    size_t length = strlen(string);
    size_t j = 0;

    for (size_t i = 0; i < length; i += 3) {
        Card c = NewCardFromChars(string[i], string[i+1]);
        hand[j] = c;
        j++;
    }
}


void TestHandClassifyStraightFlush(CuTest* tc) {
    Card hand[5];
    char output[OUTPUT_LENGTH];
    const char *straight_flushes[] = {
        "As Ks Qs Js Ts",
        "Ks Qs Js Ts 9s",
        "Qs Js Ts 9s 8s",
        "Js Ts 9s 8s 7s",
        "Ts 9s 8s 7s 6s",
        "9s 8s 7s 6s 5s",
        "8s 7s 6s 5s 4s",
        "7s 6s 5s 4s 3s",
        "6s 5s 4s 3s 2s",
        "5s 4s 3s 2s As",
        NULL
    };
    for (size_t i = 0; straight_flushes[i] != NULL; ++i) {
        snprintf(output, OUTPUT_LENGTH, "[%s] should be a straight flush", straight_flushes[i]);
        NewHandFromString(straight_flushes[i], hand);

        for (Suit s = Club; s <= Spade; ++s) {
            for (size_t j = 0; j < HAND_LENGTH; ++j) { hand[j].suit = s; }
            CuAssert(tc, output, HandClassify((const Card*)&hand) == StraightFlush);
        }
    }
}


void TestHandClassifyQuads(CuTest* tc) {
    Card hand[5];
    char output[OUTPUT_LENGTH];

    for (Rank r1 = Deuce; r1 <= Ace; ++r1) {
        for (Rank r2 = Deuce; r2 <= Ace; ++r2) {
            if (r1 == r2) continue;

            for (Suit s = Club; s <= Spade; ++s) {
                hand[0] = NewCard(r1, Club);
                hand[1] = NewCard(r1, Diamond);
                hand[2] = NewCard(r1, Heart);
                hand[3] = NewCard(r1, Spade);
                hand[4] = NewCard(r2, s);

                snprintf(output, OUTPUT_LENGTH, "[%c%c%c%c%c] should be four of a kind",
                         ranks[r1], ranks[r1], ranks[r1], ranks[r1], ranks[r2]);
                CuAssert(tc, output, HandClassify((const Card*)hand) == FourOfAKind);
            }
        }
    }
}


void TestHandClassifyFullHouse(CuTest* tc) {
    Card hand[5];
    char output[OUTPUT_LENGTH];

    for (Rank r1 = Deuce; r1 <= Ace; ++r1) {
        for (Rank r2 = Deuce; r2 <= Ace; ++r2) {
            if (r1 == r2) continue;

            hand[0] = NewCard(r1, Club);
            hand[1] = NewCard(r1, Diamond);
            hand[2] = NewCard(r1, Spade);
            hand[3] = NewCard(r2, Club);
            hand[4] = NewCard(r2, Diamond);

            snprintf(output, OUTPUT_LENGTH, "[%c%c%c%c%c] should be a fullhouse",
                     ranks[r1], ranks[r1], ranks[r1], ranks[r2], ranks[r2]);
            CuAssert(tc, output, HandClassify((const Card*)hand) == FullHouse);
        }
    }
}


void TestHandClassifyFlush(CuTest* tc) {
    Card hand[5];
    char output[OUTPUT_LENGTH];
    const char *flushes[] = {
        "As 2s 3s 4s 6s",
        "As 2s 3s 4s 7s",
        "As 2s 3s 4s 8s",
        "As 2s 3s 4s 9s",
        "As 2s 3s 4s Ts",
        "As 2s 3s 4s Js",
        "As 2s 3s 4s Qs",
        "As 2s 3s 4s Ks",
        NULL,
    };

    for (size_t i = 0; flushes[i] != NULL; ++i) {
        snprintf(output, OUTPUT_LENGTH, "[%s] should be a flush", flushes[i]);
        NewHandFromString(flushes[i], hand);
        for (Suit s = Club; s <= Spade; ++s) {
            for (size_t j = 0; j < HAND_LENGTH; ++j) { hand[j].suit = s; }
            CuAssert(tc, output, HandClassify((const Card*)&hand) == Flush);
        }
    }
}


void TestHandClassifyStraight(CuTest* tc) {
    Card hand[5];
    char output[OUTPUT_LENGTH];
    const char *straights[] = {
        "5c 4s 3h 2d Ac",
        "6s 5c 4s 3h 2d",
        "7d 6s 5c 4s 3h",
        "8h 7d 6s 5c 4s",
        "9s 8h 7d 6s 5c",
        "Tc 9s 8h 7d 6s",
        "Jd Tc 9s 8h 7d",
        "Qh Jd Tc 9s 8h",
        "Ks Qh Jd Tc 9s",
        "As Ks Qh Jd Tc",
        NULL,
    };

    for (size_t i = 0; straights[i] != NULL; ++i) {
        snprintf(output, OUTPUT_LENGTH, "[%s] should be a straight", straights[i]);
        NewHandFromString(straights[i], hand);
        CuAssert(tc, output, HandClassify((const Card*)&hand) == Straight);
    }
}


void TestHandClassifyTrips(CuTest* tc) {
    Card hand[5];
    char output[OUTPUT_LENGTH];

    for (Rank r1 = Deuce; r1 <= Ace; ++r1) {
        for (Rank r2 = Deuce; r2 <= Ace; ++r2) {
            if (r1 == r2) continue;

            for (Rank r3 = Deuce; r3 <= Ace; ++r3) {
                if (r3 == r1 || r3 == r2) continue;

                hand[0] = NewCard(r1, Club);
                hand[1] = NewCard(r1, Diamond);
                hand[2] = NewCard(r1, Spade);
                hand[3] = NewCard(r2, Club);
                hand[4] = NewCard(r3, Diamond);

                snprintf(output, OUTPUT_LENGTH, "[%c%c%c%c%c] should be three of a kind",
                         ranks[r1], ranks[r1], ranks[r1], ranks[r2], ranks[r3]);
                CuAssert(tc, output, HandClassify((const Card*)hand) == ThreeOfAKind);
            }
        }
    }
}




void TestHandClassifyTwoPair(CuTest* tc) {
    Card hand[5];
    char output[OUTPUT_LENGTH];
    const char *twopairs[] = {
        "As Ac Ks Kc Qs",
        "As Ac Qs Qc Ks",
        "As Ac Js Jc Qs",
        "As Ac Ts Tc Qs",
        "As Ac 9s 9c Qs",
        "As Ac 8s 8c Qs",
        "As Ac 7s 7c Qs",
        "As Ac 6s 6c Qs",
        "As Ac 5s 5c Qs",
        "As Ac 4s 4c Qs",
        "As Ac 3s 3c Qs",
        "As Ac 2s 2c Qs",
        NULL,
    };

    for (size_t i = 0; twopairs[i] != NULL; ++i) {
        snprintf(output, OUTPUT_LENGTH, "[%s] should be a two pair", twopairs[i]);
        NewHandFromString(twopairs[i], hand);
        CuAssert(tc, output, HandClassify((const Card*)&hand) == TwoPair);
    }
}


void TestHandClassifyPair(CuTest* tc) {
    Card hand[5];
    char output[OUTPUT_LENGTH];
    const char *pairs[] = {
        "As Ac Ks 2c Qs",
        "As Ac Qs 2c Ks",
        "As Ac Js 2c Qs",
        "As Ac Ts 2c Qs",
        "As Ac 9s 2c Qs",
        "As Ac 8s 2c Qs",
        "As Ac 7s 2c Qs",
        "As Ac 6s 2c Qs",
        "As Ac 5s 2c Qs",
        "As Ac 4s 2c Qs",
        "As Ac 3s 2c Qs",
        "As Ac 2s 3c Qs",
        NULL,
    };

    for (size_t i = 0; pairs[i] != NULL; ++i) {
        snprintf(output, OUTPUT_LENGTH, "[%s] should be a pair", pairs[i]);
        NewHandFromString(pairs[i], hand);
        CuAssert(tc, output, HandClassify((const Card*)&hand) == Pair);
    }
}


void TestHandClassifyHighCard(CuTest* tc) {
    Card hand[5];
    char output[OUTPUT_LENGTH];
    const char *highcards[] = {
        "As 3c Ks 2c Qs",
        "As 3c Qs 2c Ks",
        "As 3c Js 2c Qs",
        "As 3c Ts 2c Qs",
        "As 3c 9s 2c Qs",
        "As 3c 8s 2c Qs",
        "As 3c 7s 2c Qs",
        "As 3c 6s 2c Qs",
        "As 3c 5s 2c Qs",
        "As 3c 4s 2c Qs",
        "As 4c 3s 2c Qs",
        "As 3c 2s 4c Qs",
        NULL,
    };

    for (size_t i = 0; highcards[i] != NULL; ++i) {
        snprintf(output, OUTPUT_LENGTH, "[%s] should be a high card", highcards[i]);
        NewHandFromString(highcards[i], hand);
        CuAssert(tc, output, HandClassify((const Card*)&hand) == HighCard);
    }
}


CuSuite* HandUtilSuite() {
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestHandClassifyStraightFlush);
    SUITE_ADD_TEST(suite, TestHandClassifyQuads);
    SUITE_ADD_TEST(suite, TestHandClassifyFullHouse);
    SUITE_ADD_TEST(suite, TestHandClassifyFlush);
    SUITE_ADD_TEST(suite, TestHandClassifyStraight);
    SUITE_ADD_TEST(suite, TestHandClassifyTrips);
    SUITE_ADD_TEST(suite, TestHandClassifyTwoPair);
    SUITE_ADD_TEST(suite, TestHandClassifyPair);
    SUITE_ADD_TEST(suite, TestHandClassifyHighCard);

    return suite;
}
