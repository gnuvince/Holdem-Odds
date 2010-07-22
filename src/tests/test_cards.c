#include <string.h>

#include "CuTest.h"
#include "cards.h"

char ranks[] = "23456789TJQKA";
char suits[] = "chds";
size_t ranksLength = 13;
size_t suitsLength = 4;

void TestCharToSuit(CuTest* tc) {
    // Valid suits
    CuAssert(tc, "c isn't Club", CharToSuit('c') == Club);
    CuAssert(tc, "d isn't Diamond", CharToSuit('d') == Diamond);
    CuAssert(tc, "h isn't Heart", CharToSuit('h') == Heart);
    CuAssert(tc, "s isn't Spade", CharToSuit('s') == Spade);

    // Other characters are invalid suit representations
    char invalidSuits[] = "abefgijklmnopqrtuvwxyz"
        "ABCDEFGHIJKLMNOQRSTUVWXYZ"
        "0123456789";

    size_t length = strlen(invalidSuits);
    char output[] = "_ should not be a valid suit";
    for (size_t i = 0; i < length; ++i) {
        output[0] = invalidSuits[i];
        CuAssert(tc, output, CharToSuit(invalidSuits[i]) == InvalidSuit);
    }
}


void TestCharToRank(CuTest* tc) {
    // Valid ranks
    CuAssert(tc, "2 isn't Deuce", CharToRank('2') == Deuce);
    CuAssert(tc, "3 isn't Trey", CharToRank('3') == Trey);
    CuAssert(tc, "4 isn't Four", CharToRank('4') == Four);
    CuAssert(tc, "5 isn't Five", CharToRank('5') == Five);
    CuAssert(tc, "6 isn't Six", CharToRank('6') == Six);
    CuAssert(tc, "7 isn't Seven", CharToRank('7') == Seven);
    CuAssert(tc, "8 isn't Eight", CharToRank('8') == Eight);
    CuAssert(tc, "9 isn't Nine", CharToRank('9') == Nine);
    CuAssert(tc, "T isn't Ten", CharToRank('T') == Ten);
    CuAssert(tc, "J isn't Jack", CharToRank('J') == Jack);
    CuAssert(tc, "Q isn't Queen", CharToRank('Q') == Queen);
    CuAssert(tc, "K isn't King", CharToRank('K') == King);
    CuAssert(tc, "A isn't Ace", CharToRank('A') == Ace);

    char invalidRanks[] = "abcdefghijklmnopqrstuvwxyz"
        "BCDEFGHILMNOPRSUVWXYZ01";
    size_t length = strlen(invalidRanks);
    char output[] = "_ should not be a valid rank";
    for (size_t i = 0; i < length; ++i) {
        output[0] = invalidRanks[i];
        CuAssert(tc, output, CharToRank(invalidRanks[i]) == InvalidRank);
    }
}

void TestNewCard(CuTest* tc) {
    char output[] = "__ isn't a valid card";

    for (size_t i = 0; i < ranksLength; ++i) {
        for (size_t j = 0; j < suitsLength; ++j) {
            Card c;
            int result = NewCard(&c, ranks[i], suits[j]);
            output[0] = ranks[i];
            output[1] = suits[j];
            CuAssert(tc, output, result == 1);
        }
    }

    char invalidRanks[] = "abcdefghijklmnopqrstuvwxyzBCDEFGHILMNOPRSUVWXYZ01";
    char invalidSuits[] = "abefgijklmnopqrtuvwxyzABCDEFGHIJKLMNOQRSTUVWXYZ"
        "0123456789";
    char output2[] = "__ should be a valid card";
    size_t invalidRanksLength = strlen(invalidRanks);
    size_t invalidSuitsLength = strlen(invalidSuits);

    for (size_t i = 0; i < invalidRanksLength; ++i) {
        for (size_t j = 0; j < invalidSuitsLength; ++j) {
            Card c;
            int result = NewCard(&c, invalidRanks[i], invalidSuits[j]);
            output2[0] = invalidRanks[i];
            output2[1] = invalidSuits[j];
            CuAssert(tc, output2, result == 0);
        }
    }
}

void TestCompareCards(CuTest* tc) {
    // Equal cards
    for (size_t i = 0; i < ranksLength; ++i) {
        for (size_t j = 0; j < suitsLength; ++j) {
            for (size_t k = 0; k < suitsLength; ++k) {
                Card c1, c2;
                NewCard(&c1, ranks[i], suits[j]);
                NewCard(&c2, ranks[i], suits[k]);

                char output[] = "__ != __";
                output[0] = ranks[i];
                output[1] = suits[j];
                output[6] = ranks[i];
                output[7] = suits[k];
                CuAssert(tc, output, CompareCards(&c1, &c2) == 0);
            }
        }
    }

    // Card1 < Card2
    for (size_t i = 0; i < ranksLength-1; ++i) {
        for (size_t i2 = i+1; i2 < ranksLength; ++i2) {
            for (size_t j = 0; j < suitsLength; ++j) {
                for (size_t k = 0; k < suitsLength; ++k) {
                    Card c1, c2;
                    NewCard(&c1, ranks[i], suits[j]);
                    NewCard(&c2, ranks[i2], suits[k]);

                    char output[] = "__ > __";
                    output[0] = ranks[i];
                    output[1] = suits[j];
                    output[5] = ranks[i2];
                    output[6] = suits[k];
                    CuAssert(tc, output, CompareCards(&c1, &c2) < 0);
                    CuAssert(tc, output, CompareCards(&c2, &c1) > 0);
                }
            }
        }
    }

    Card c;
    NewCard(&c, 'A', 's');
    CuAssert(tc, "c1 as NULL should be 1", CompareCards(NULL, &c) == 1);
    CuAssert(tc, "c2 as NULL should be -1", CompareCards(&c, NULL) == -1);
}


CuSuite* CardUtilSuite() {
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestCharToSuit);
    SUITE_ADD_TEST(suite, TestCharToRank);
    SUITE_ADD_TEST(suite, TestNewCard);
    SUITE_ADD_TEST(suite, TestCompareCards);

    return suite;
}


