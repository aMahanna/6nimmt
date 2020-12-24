#ifndef CARD_H
#define CARD_H

#include <string>  
#include <sstream>      
using namespace std;

/**
	* Class Card
    * Each card has a card number and a bullHead value
 */
class Card {                                   
    int bullHeads; 
    int cardNum;
 public: 

    // Create a Card and set the number of bullHeads based on the game's rules
    Card(int n): cardNum(n) { 
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
    // Copy constructor 
    Card(const Card& c): bullHeads(c.bullHeads),cardNum(c.cardNum){}
    
    Card() {}
    
    // Operator * overload to return the number of bullHeads
    int operator*() const { 
        return bullHeads; 
    } 
    
    // Operator < overload to compare two cardNums 
    bool operator<(const Card& c) const {
        return cardNum < c.cardNum; 
    }
    
    int getCardNum() const { 
        return cardNum;
    } 
    
    /**
	 * toString()
     * Prints the card values in a readable format
	 */
    const string toString() const {
            stringstream ss (stringstream::in | stringstream::out);
            ss << "(" << cardNum << ", " << bullHeads << ")"; 
            return ss.str();
    }
};

/**
     * Operator << overload for cout operations
 */ 
inline ostream& operator<<(ostream &left, const Card &right) {
    left << right.toString();
    return left;
}
#endif

