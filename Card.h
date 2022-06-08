#ifndef RANDOMIZATION_CARD_H
#define RANDOMIZATION_CARD_H

#include <iostream>

using namespace std;

/*
 * Card Class Contains:
 * Fields for Rank and Suit
 * Constructor for Each Combination of Parameters initRank and initSuit
 * Method to Randomize This Card (By Randomizing rank and suit)
 * Overloaded << Operator
 */
class Card
{
public:
    // Enums for rank and suit
    enum rankEnum {ace = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7,
            eight = 8, nine = 9, ten = 10, jack = 11, queen = 12, king = 13};
    enum suitEnum {clubs = 1, diamonds = 2, hearts = 3, spades = 4};

    // Constructors
    Card();
    Card(rankEnum initRank, suitEnum initSuit, int initDeckPos);

    // Getters
    rankEnum getRank() const;
    suitEnum getSuit() const;
    int getDeckPos() const;

    // Setters
    void setRank(rankEnum newRank);
    void setSuit(suitEnum newSuit);
    void setDeckPos(int newDeckPos);

    // Randomizes This Card
    // Modifies rank and suit
    void randomize();

    // Overloaded Operators
    friend bool operator < (const Card& lhs, const Card& rhs);
    friend bool operator > (const Card& lhs, const Card& rhs);
    friend bool operator <= (const Card& lhs, const Card& rhs);
    friend bool operator >= (const Card& lhs, const Card& rhs);
    friend bool operator == (const Card& lhs, const Card& rhs);
    friend ostream& operator << (ostream& outs, const Card& card);

    // Constants
    static const int RANKS = 13;
    static const int SUITS = 4;

private:
    // Fields
    rankEnum rank;
    suitEnum suit;
    int deckPos;
};

#endif //RANDOMIZATION_CARD_H
