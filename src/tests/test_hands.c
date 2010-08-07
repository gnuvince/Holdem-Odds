#include <stdio.h>
#include <string.h>

#include "CuTest.h"
#include "cards.h"
#include "hands.h"


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
    char output[512]; // Error messages should not exceed this length.
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
        snprintf(output, 512, "[%s] should be a straight flush", straight_flushes[i]);
        NewHandFromString(straight_flushes[i], hand);
        CuAssert(tc, output, HandClassify((const Card*)&hand) == StraightFlush);
    }

    const char *not_straight_flushes[] = {
        "As Ks Qs Js 9s", // Flush, but not straight
        "Ks Qs Js Ts 9c", // Straight, but not flush
        "Ac Ad Ah As Ks", // Neither flush nor straight
        NULL
    };

    for (size_t i = 0; not_straight_flushes[i] != NULL; ++i) {
        snprintf(output, 512, "[%s] should not be a straight flush", not_straight_flushes[i]);
        NewHandFromString(not_straight_flushes[i], hand);
        CuAssert(tc, output, HandClassify((const Card*)&hand) != StraightFlush);
    }
}


CuSuite* HandUtilSuite() {
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestHandClassifyStraightFlush);

    return suite;
}
