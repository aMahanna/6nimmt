#ifndef PLAYER_H 
#define PLAYER_H 
#include "Card.h"

#include <string>  
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm> 
using namespace std;

class Card; 

/**
	* Player class
	* Has a hand (vector<Card>), points and a name
 */
class Player {
    std::vector<Card> hand;    
    int points;                 
    string name;

 public:
    
    Player(string n, int startingPts): name(n), points(startingPts) {} 
    
    std::string getName() const { return name; } 
    int getPoints() const { return points; }

    
    // Operator += & -= overload to add/remove points
    Player& operator+=(int pts) { points+= pts; return *this; } 
    Player& operator-=(int pts) { points -= pts; return *this; } 
    
    
    // Returns an iterator at the start of the player's hand
    std::vector<Card>::const_iterator begin() const { 
        return hand.begin();
    }
    
    
    // Returns an iterator at the end of the player's hand 
    std::vector<Card>::const_iterator end() const { 
        return hand.end();
    }
    
    // Operator ! overload to check if the player still has cards or not
    bool operator!() const {
        return !hand.empty();
    }
    
    
    // Operator += overload to add a card to the player's hand
    Player& operator+=(const Card& c) { 
        hand.push_back(c);
        sort(hand.begin(), hand.end());
        return *this; 
    }
    
    // Operator -= overload to find & remove a card from the player's hand
    Player& operator-=(const Card& c) {
        for (vector<Card>::const_iterator it = hand.begin(); it != hand.end(); it++) {
            if (it->getCardNum() == c.getCardNum()) {
                hand.erase(it);
                break;
            }
        }
        
        return *this; 
    }
    
 
    bool operator<(const Player& j) const {
        return points < j.points; 
    }
    
    /**
	 * toString()
	 * Prints the player's info in a readable format
	 */
    const string toString() const {
            stringstream ss (stringstream::in | stringstream::out);
            ss << "\nPlayer: " << name << "\n";
            ss << "Points: " << points << "\n";
            ss << "Hand: {";
            for (vector<Card>::const_iterator it = hand.begin(); it != hand.end(); it++) { // On utilise un itérateur pour imprimer la hand
                ss << *it;
            }
            ss << "}";
            return ss.str();
    }
};

inline ostream& operator<<(ostream &left, const Player &right) { // (2)
    left << right.toString();
    return left;
}

#endif