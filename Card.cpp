#include "Card.h"
#include <cstdlib>
#include <ctime>

// Constructors
Card::Card() : rank(), suit(), deckPos() {}
Card::Card(Card::rankEnum initRank, Card::suitEnum initSuit, int initDeckPos) : rank(initRank), suit(initSuit), deckPos(initDeckPos) {}

// Getters
Card::rankEnum Card::getRank() const
{
    return rank;
}

Card::suitEnum Card::getSuit() const
{
    return suit;
}

int Card::getDeckPos() const
{
    return deckPos;
}

// Setters
void Card::setRank(rankEnum newRank)
{
    rank = newRank;
}

void Card::setSuit(suitEnum newSuit)
{
    suit = newSuit;
}

void Card::setDeckPos(int newDeckPos)
{
    deckPos = newDeckPos;
}

// Method to Randomize This Card
void Card::randomize()
{
    srand(time(NULL));
    rank = static_cast<rankEnum>(rand() % RANKS + 1);
    suit = static_cast<suitEnum>(rand() % SUITS + 1);
}

// Overloaded Operators
bool operator < (const Card& lhs, const Card& rhs)
{
    return lhs.rank < rhs.rank || lhs.rank == rhs.rank && lhs.suit < rhs.suit;
}

bool operator > (const Card& lhs, const Card& rhs)
{
    return lhs.rank > rhs.rank || lhs.rank == rhs.rank && lhs.suit > rhs.suit;
}

bool operator <= (const Card& lhs, const Card& rhs)
{
    return lhs.rank < rhs.rank || lhs.rank == rhs.rank && lhs.suit <= rhs.suit;
}

bool operator >= (const Card& lhs, const Card& rhs)
{
    return lhs.rank > rhs.rank || lhs.rank == rhs.rank && lhs.suit >= rhs.suit;
}

bool operator == (const Card& lhs, const Card& rhs)
{
    return lhs.rank == rhs.rank && lhs.suit == rhs.suit;
}

ostream& operator << (ostream& outs, const Card& card)
{
    string rankString = to_string(card.rank);
    if(card.rank == Card::ace)
    {
        rankString = "Ace";
    }
    else if(card.rank == Card::jack)
    {
        rankString = "Jack";
    }
    else if(card.rank == Card::queen)
    {
        rankString = "Queen";
    }
    else if(card.rank == Card::king)
    {
        rankString = "King";
    }

    string suitString = "Clubs";
    if(card.suit == Card::diamonds)
    {
        suitString = "Diamonds";
    }
    else if(card.suit == Card::hearts)
    {
        suitString = "Hearts";
    }
    else if(card.suit == Card::spades)
    {
        suitString = "Spades";
    }

    outs << rankString << " of " << suitString;
    return outs;
}
