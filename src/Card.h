#pragma once
#ifndef CARD_H
#define CARD_H

#include <sstream>
#include <string>

/**
 * Class Card
 * Each card has a card number and a bullHead value
 */
class Card {
  int bullHeads;
  int cardNum;





public:
  // Constructors Empty, Parameterized, & Copy
  Card();Card(int n);Card(const Card &c);

  // Operator * overload to return the number of bullHeads
  int operator*() const;
  // Operator < overload to compare two cardNums
bool operator<(const Card &c) const;

  int getCardNum() const;

  const std::string toString() const;
};

/**
 * Operator << overload for cout operations
 */
inline std::ostream &operator<<(std::ostream &left, const Card &right) {
  left << right.toString(); return left;
}
#endif
