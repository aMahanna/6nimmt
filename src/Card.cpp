#include "Card.h"

Card::Card() {}

// Create a Card and set the number of bullHeads based on the game's rules
Card::Card(int n) : cardNum(n) {
  if (cardNum % 11 == 0) {
    bullHeads = cardNum == 55 ? 7 : 5;
  } else if (cardNum % 10 == 0) {
    bullHeads = 3;
  } else if (cardNum % 5 == 0) {
    bullHeads = 2;
  } else {
    bullHeads = 1;
  }
}

Card::Card(const Card &c) : bullHeads(c.bullHeads), cardNum(c.cardNum) {}

int Card::operator*() const { return bullHeads; }

bool Card::operator<(const Card &c) const { return cardNum < c.cardNum; }

int Card::getCardNum() const { return cardNum; }

const std::string Card::toString() const {
  std::stringstream ss(std::stringstream::in | std::stringstream::out);
  ss << "(" << cardNum << ", " << bullHeads << ")";
  return ss.str();
}