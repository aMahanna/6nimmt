#ifndef DECK_H 
#define DECK_H 

/**
	* Deck class
	* Represents the deck of 104 cards created for the game
 */
template <typename T>
class Deck {
    std::vector<T> elemList;  
 public:

    Deck() {}
    Deck(const vector<T>& copyList) {
        elemList = copyList;
    }
    
    
    // Shuffles the vector num times
    void shuffleDeck(int num) {					
        for (int i = 0; i < num; i++) {
           std::random_shuffle(elemList.begin(), elemList.end());
        }
    }
    
    
    // Operator += overload to add a card to the bottom of the deck
    Deck& operator+=(const T& e) {         
        elemList.insert(elemList.begin(), e);
        return *this; 
    }
    
    // Operator -- overload to remove a card from the top of the deck and return it
    T operator--() {						
        T val = elemList.back();
        elemList.pop_back();
        return val; 
    }
};

#endif