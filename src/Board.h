#ifndef BOARD_H
#define BOARD_H

#include <climits>

class Card;

/**
	* The 6nimmt Board class
	* Represents the four rows of the game board using an array of Card vectors
*/
class  Board {
    int rowChoice; 
    const int NUM_ROWS;
    const int ROW_MAX;
    const std::vector<Card> EMPTY_VECTOR;
    
    vector<Card> rows[4];
    
    void resetRowChoice() {
        rowChoice = -1;
    }
    
 public:
    Board(): NUM_ROWS(4), ROW_MAX(5), rowChoice(-1) {
        for (int i = 0; i < NUM_ROWS; i++) {
            rows[i] = vector<Card>(ROW_MAX);
        }
    }

    // Operator ~ overload for resetting all board rows
    void operator~() {						
        for (int i = 0; i < NUM_ROWS; i++) {
            rows[i].clear();
        }
    }    
    
    // Operator [] overload for setting the rowChoice variable
    Board& operator[](int i) {
        rowChoice = i; 
        return *this; 
    }
    
    
    /**
	 * Operator << overload to load a card into one of the rows
	*/
    std::pair<std::vector<Card>,bool> operator<<(const Card& c) {		
        // Case 1: rowChoice has been set, load card into the respective row 
        if (rowChoice != -1) {
            std::vector<Card> copy = rows[rowChoice];
            rows[rowChoice].clear(); 
            rows[rowChoice].push_back(c);
            
            resetRowChoice();  // reset the rowChoice
            return make_pair(copy, true);
        }
        // -------------------------------------------------
        
        // Case 2: One of the rows are empty, insert card into that row
        for (int i = 0; i < NUM_ROWS; i++) {
            if (rows[i].empty()) {
                rows[i].insert(rows[i].begin(), c); 
                return make_pair(EMPTY_VECTOR, true);
            }
        }
        // -------------------------------------------------
        
        // Case 3: None of the vectors are empty, find the most optimal row 
        int cardNum = c.getCardNum(); 
        int min = INT_MAX; 
        int index = -1;
        int diff; 
        for (int i = 0; i < NUM_ROWS; i++) { // Find the row with the smallest difference 
            diff = cardNum - rows[i].back().getCardNum();
            if (diff > 0 && diff < min) { 		
                min = diff;
                index = i; 
            }
        }
        
        if (index == -1) {                          // No valid row found, return false 
            return make_pair(EMPTY_VECTOR, false);
            
        } else if (rows[index].size() != ROW_MAX) { // Valid row found, card inserted
            rows[index].push_back(c); 
            return make_pair(EMPTY_VECTOR, true); 
            
        } else {                                    // Valid row found, but row is full
            std::vector<Card> copy = rows[index];
            rows[index].clear(); 
            rows[index].push_back(c); 
            return make_pair(copy, true);
        }
        // -------------------------------------------------
    }
    
    /**
	 * toString()
     * Prints the value of the rows in a readable format
	*/
    const string toString() const {
            stringstream ss (stringstream::in | stringstream::out);  
            ss << "\n------------------------------------------------------";
            for (int i = 0; i < NUM_ROWS; i++) { 								
                ss << "\nRow " << i+1 << ": {";
                for (vector<Card>::const_iterator it = rows[i].begin(); it != rows[i].end(); it++) { 
                    ss << *it; 	// Uses the toString() of the Card class
                }
                ss << "}";
            }
            ss << "\n------------------------------------------------------\n";
            return ss.str();
    }
};

/**
	 * Operator << overload for cout operations
 */ 
inline ostream& operator<<(ostream &left, const Board &right) { // (2)
    left << right.toString();
    return left;
}

#endif