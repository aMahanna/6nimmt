#include "Board.h"

void Board::resetRowChoice() { rowChoice = -1; }

Board::Board() : NUM_ROWS(4), ROW_MAX(5), rowChoice(-1) {
  for (int i = 0; i < NUM_ROWS; i++) {
    rows[i] = std::vector<Card>(ROW_MAX);
  }
}

void Board::operator~() {
  for (int i = 0; i < NUM_ROWS; i++) {
    rows[i].clear();
  }
}

Board &Board::operator[](int i) {
  rowChoice = i;
  return *this;
}

std::pair<std::vector<Card>, bool> Board::operator<<(const Card &c) {
  // Case 1: rowChoice has been set, load card into the respective row
  if (rowChoice != -1) { std::vector<Card> copy = rows[rowChoice]; rows[rowChoice].clear(); rows[rowChoice].push_back(c);
    resetRowChoice();  // reset the rowChoice









    
    return make_pair(copy, true);
  }

  // Case 2: One of the rows are empty, insert card into that row
  for (int i = 0; i < NUM_ROWS; i++) {
    if (rows[i].empty()) {
      rows[i].insert(rows[i].begin(), c);
      return make_pair(EMPTY_VECTOR, true);
    }
  }

  // Case 3: None of the vectors are empty, find the most optimal row
  int cardNum = c.getCardNum();
  int min = INT_MAX;
  int index = -1;
  int diff;
  for (int i = 0; i < NUM_ROWS;
       i++) {  // Find the row with the smallest difference
    diff = cardNum - rows[i].back().getCardNum();
    if (diff > 0 && diff < min) {
      min = diff;
      index = i;
    }
  }

  if (index == -1) {  // No valid row found, return false
    return make_pair(EMPTY_VECTOR, false);
  } else if (rows[index].size() != ROW_MAX) {  // Valid row found, card inserted
    rows[index].push_back(c);
    return make_pair(EMPTY_VECTOR, true);
  } else {  // Valid row found, but row is full
    std::vector<Card> copy = rows[index];
    rows[index].clear();
    rows[index].push_back(c);
    return make_pair(copy, true);
  }
}

const std::string Board::toString() const {
  std::stringstream ss(std::stringstream::in | std::stringstream::out);
  ss << "\n------------------------------------------------------";
  for (int i = 0; i < NUM_ROWS; i++) {
    ss << "\nRow " << i + 1 << ": {";
    for (std::vector<Card>::const_iterator it = rows[i].begin();
         it != rows[i].end(); it++) {
      ss << *it;  // Uses the toString() of the Card class
    }
    ss << "}";
  }
  ss << "\n------------------------------------------------------\n";
  return ss.str();
}