#include <string.h>

#include "CuTest.h"
#include "cards.h"

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

CuSuite* CardUtilSuite() {
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestCharToSuit);
    SUITE_ADD_TEST(suite, TestCharToRank);

    return suite;
}


