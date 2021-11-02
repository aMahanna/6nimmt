#include "Player.h"

Player::Player(std::string n, int startingPts) : name(n), points(startingPts) {}

std::string Player::getName() const { return name; }

int Player::getPoints() const { return points; }

std::vector<Card>::const_iterator Player::begin() const { return hand.begin(); }

std::vector<Card>::const_iterator Player::end() const { return hand.end(); }

Player &Player::operator+=(int pts) {
  points += pts;
  return *this;
}

Player &Player::operator-=(int pts) {
  points -= pts;
  return *this;
}

Player &Player::operator+=(const Card &c) {
  hand.push_back(c);
  sort(hand.begin(), hand.end());
  return *this;
}

Player &Player::operator-=(const Card &c) {
  for (std::vector<Card>::const_iterator it = hand.begin(); it != hand.end();
       it++) {
    if (it->getCardNum() == c.getCardNum()) {
      hand.erase(it);
      break;
    }
  }

  return *this;
}

bool Player::operator!() const { return !hand.empty(); }

bool Player::operator<(const Player &j) const { return points < j.points; }

const std::string Player::toString() const {
  std::stringstream ss(std::stringstream::in | std::stringstream::out);
  ss << "\nPlayer: " << name << "\n";
  ss << "Points: " << points << "\n";
  ss << "Hand: {";
  for (std::vector<Card>::const_iterator it = hand.begin(); it != hand.end();
       it++) {  // On utilise un itérateur pour imprimer la hand
    ss << *it;
  }
  ss << "}";
  return ss.str();
}
