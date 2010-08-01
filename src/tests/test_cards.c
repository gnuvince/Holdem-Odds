#include <stdio.h>
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
    for (Rank r = Deuce; r <= Ace; ++r) {
        for (Suit s = Club; s <= Spade; ++s) {
            Card c = NewCard(r, s);
            char output[] = "__ should be valid";
            output[0] = ranks[r-1];
            output[1] = suits[s-1];
            CuAssert(tc, output, c.rank != InvalidRank);
            CuAssert(tc, output, c.suit != InvalidSuit);
            CuAssert(tc, output, CardIsValid(&c));
        }
    }

    /* Make sure out-of-bounds values cause an invalid value */
    {
        Card c;
        c = NewCard(InvalidRank, Spade);
        CuAssert(tc, "InvalidRank is an invalid rank", !CardIsValid(&c));
        CuAssert(tc, "InvalidRank is an invalid rank", c.rank == InvalidRank && c.suit == InvalidSuit);

        c = NewCard(Ace+1, Spade);
        CuAssert(tc, "Ace+1 is an invalid rank", !CardIsValid(&c));
        CuAssert(tc, "Ace+1 is an invalid rank", c.rank == InvalidRank && c.suit == InvalidSuit);

        c = NewCard(Deuce, InvalidSuit);
        CuAssert(tc, "InvalidSuit is an invalid suit", !CardIsValid(&c));
        CuAssert(tc, "InvalidSuit is an invalid suit", c.rank == InvalidRank && c.suit == InvalidSuit);

        c = NewCard(Deuce, Spade+1);
        CuAssert(tc, "Spade+1 is an invalid suit", !CardIsValid(&c));
        CuAssert(tc, "Spade+1 is an invalid suit", c.rank == InvalidRank && c.suit == InvalidSuit);
    }
}


void TestNewCardFromChars(CuTest* tc) {
    char output[] = "__ isn't a valid card";

    for (size_t i = 0; i < ranksLength; ++i) {
        for (size_t j = 0; j < suitsLength; ++j) {
            Card c = NewCardFromChars(ranks[i], suits[j]);
            output[0] = ranks[i];
            output[1] = suits[j];
            CuAssert(tc, output, CardIsValid(&c));
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
            Card c = NewCardFromChars(invalidRanks[i], invalidSuits[j]);
            output2[0] = invalidRanks[i];
            output2[1] = invalidSuits[j];
            CuAssert(tc, output2, !CardIsValid(&c));
        }
    }
}


void TestNewCardFromString(CuTest* tc) {
    char output[] = "__ isn't a valid card";

    for (size_t i = 0; i < ranksLength; ++i) {
        for (size_t j = 0; j < suitsLength; ++j) {
            char s[] = "__";
            s[0] = ranks[i];
            s[1] = suits[j];
            Card c = NewCardFromString(s);
            output[0] = ranks[i];
            output[1] = suits[j];
            CuAssert(tc, output, CardIsValid(&c));
        }
    }


    Card c;

    c = NewCardFromString("");
    CuAssert(tc, "Invalid length input", !CardIsValid(&c));
    CuAssert(tc, "Invalid lenght input", c.rank == InvalidRank && c.suit == InvalidSuit);

    c = NewCardFromString("A");
    CuAssert(tc, "Invalid length input", !CardIsValid(&c));
    CuAssert(tc, "Invalid lenght input", c.rank == InvalidRank && c.suit == InvalidSuit);

    c = NewCardFromString("AAA");
    CuAssert(tc, "Invalid length input", !CardIsValid(&c));
    CuAssert(tc, "Invalid lenght input", c.rank == InvalidRank && c.suit == InvalidSuit);
}

void TestCardCompareEqual(CuTest* tc) {
    for (Rank r = Deuce; r <= Ace; ++r) {
        for (Suit s1 = Club; s1 <= Spade; ++s1) {
            for (Suit s2 = Club; s2 <= Spade; ++s2) {
                Card c1 = NewCard(r, s1);
                Card c2 = NewCard(r, s2);

                char output[9];
                char c1Str[3];
                char c2Str[3];
                CardToString(c1Str, &c1);
                CardToString(c2Str, &c2);

                snprintf(output, 8, "%s != %s", c1Str, c2Str);
                CuAssert(tc, output, CardCompare(&c1, &c2) == 0);
            }
        }
    }
}


CuSuite* CardUtilSuite() {
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestCharToSuit);
    SUITE_ADD_TEST(suite, TestCharToRank);
    SUITE_ADD_TEST(suite, TestNewCard);
    SUITE_ADD_TEST(suite, TestNewCardFromChars);
    SUITE_ADD_TEST(suite, TestNewCardFromString);
    SUITE_ADD_TEST(suite, TestCardCompareEqual);

    return suite;
}


