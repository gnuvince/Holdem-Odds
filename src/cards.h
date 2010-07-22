#ifndef _CARDS_H

#define _CARDS_H

#include <stdlib.h>

#define RANKS_PER_DECK 13
#define SUITS_PER_DECK 4


#define RANK_CHARS "23456789TJQKA"
#define SUIT_CHARS "cdhs"


typedef enum _Suit { InvalidSuit, Club, Diamond, Heart, Spade } Suit;
typedef enum _Rank {
    InvalidRank, Deuce, Trey, Four, Five, Six, Seven,
    Eight, Nine, Ten, Jack, Queen, King, Ace
} Rank;

typedef struct {
    Rank rank;
    Suit suit;
} Card;


size_t    indexOf(char, const char*, size_t);
int       NewCard(Card*, char, char);
Rank      CharToRank(char);
Suit      CharToSuit(char);
int       CompareCards(const Card*, const Card*);
void      CardToString(char *, const Card*);

#endif
