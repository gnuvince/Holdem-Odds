#include <stddef.h>

#include "bucket.h"
#include "cards.h"


void BucketAdd(Bucket* bucket, const Card* card) {
    if (bucket->count == 4)
        return;

    bucket->cards[bucket->count] = *card;
    bucket->count++;
}
