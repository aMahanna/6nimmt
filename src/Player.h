#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class Card;

/**
 * Player class
 * Has a hand (vector<Card>), points and a name
 */
class Player
{
    std::vector<Card> hand;
    int points;
    std::string name;

  public:
    Player(std::string n, int startingPts);

    std::string getName() const;
    int getPoints() const;

    // Returns an iterator at the start of the player's hand
    std::vector<Card>::const_iterator begin() const;
    // Returns an iterator at the end of the player's hand
    std::vector<Card>::const_iterator end() const;

    // Operator += & -= overload to add/remove points
    Player &operator+=(int pts);
    Player &operator-=(int pts);
    // Operator += overload to add a card to the player's hand
    Player &operator+=(const Card &c);
    // Operator -= overload to find & remove a card from the player's hand
    Player &operator-=(const Card &c);

    // Operator ! overload to check if the player still has cards or not
    bool operator!() const;
    // Operator < overload to check if player j has more points than this player
    bool operator<(const Player &j) const;

    /**
     * toString()
     * Prints the player's info in a readable format
     */
    const std::string toString() const;
};

inline std::ostream &operator<<(std::ostream &left, const Player &right)
{ // (2)
    left << right.toString();
    return left;
}

#endif