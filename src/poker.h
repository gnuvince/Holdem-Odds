#ifndef _POKER_H

#define _POKER_H

typedef enum _Suit { InvalidSuit, Club, Diamond, Heart, Spade } Suit;
typedef enum _Rank {
    InvalidRank, Deuce, Trey, Four, Five, Six, Seven,
    Eight, Nine, Ten, Jack, Queen, King, Ace
} Rank;

typedef struct {
    Rank rank;
    Suit suit;
} Card;


int NewCard(Card*, char, char);
Rank CharToRank(char);
Suit CharToSuit(char);

#endif
