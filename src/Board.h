#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Card.h"
// #include <climits>

/**
 * The 6nimmt Board class
 * Represents the four rows of the game board using an array of Card vectors
 */
class Board {
  int rowChoice;
  const int NUM_ROWS;
  const int ROW_MAX;
  const std::vector<Card> EMPTY_VECTOR;
  std::vector<Card> rows[4];
  void resetRowChoice();

 public:
  Board();

  // Operator ~ overload for resetting all board rows
  void operator~();

  // Operator [] overload for setting the rowChoice variable
  Board &operator[](int i);

  // Operator << overload to load a card into one of the rows
  std::pair<std::vector<Card>, bool> operator<<(const Card &c);

  const std::string toString() const;
};

/**
 * Operator << overload for cout operations
 */
inline std::ostream &operator<<(std::ostream &left,
                                const Board &right) {  // (2)
  left << right.toString();
  return left;
}

#endif