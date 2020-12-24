#include "Card.h"
#include "Player.h" 
#include "Deck.h"
#include "Board.h"

#include <stdio.h>
#include <list>  
 
/**
	* createDeck()
    * creates a deck of 104 Cards and returns it
*/
Deck<Card> createDeck() {
    std::vector<Card> cardList;  
    for (int i = 1; i < 105; i++) {
        Card carte(i);
        cardList.push_back(carte); 
    }
    
    Deck<Card> deck(cardList); 
    return deck; 
}

/**
	 * requestCard()
     * Asks player p to pick a card from his hand
*/
Card requestCard(Player& p) {
    cout << p << endl;
    
    Card cardChosen; 
    int choice = 0;
    bool valid = false;
    do {
        cout << "--> " << p.getName() << ", choose a card from your hand to add onto the board: "; 
        cin >> choice;
        
        if (cin.fail()) {
            cout << "Invalid Input: Please enter a number only" << endl; 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } else {
           for (vector<Card>::const_iterator it = p.begin(); it != p.end(); it++) {
                if (it->getCardNum() == choice) {
                    cardChosen = *it;    
                    p -= cardChosen;      
                    valid = true;        
                    break; 
                }
            } 
        }
        
    } while (!valid); 


    return cardChosen;
}

/**
	 * requestRow()
     * Asks player p to choose a row to clear, allowing them to place their selected card on the board 
*/
int requestRow(const Player* p) {
    cout << "\n" << p->getName() << ", you will have to pick up all the cards belonging to a row in order to place the card you chose." << endl;
    int choice = 0;
    bool valid = false;
    do {
        cout << "--> choose a row from 1 to 4: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid Input: Please enter a number only" << endl; 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } else if (choice >= 1 && choice <= 4) {
            valid = true;             
        }
        
    } while (!valid);
    
    return choice-1;    
}

/**
     * requestRow()
     * Asks player p to choose a row to clear, allowing them to place their selected card on the board 
*/
 std::list<Player> setupPlayers() {
    int numPlayers = 0;
    bool valid = false;
    do {
        cout << "--> This game plays for 2 - 10 players. Please choose the number of players: ";
        cin >> numPlayers;

        if (cin.fail()) {
            cout << "Invalid Input: Please enter a number only" << endl; 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } else if (numPlayers >= 2 && numPlayers <= 10) {
            valid = true;             
        }
    } while (!valid);

    std::list<Player> players;
    std:string pName;
    const int defaultPtns(66); 
    for (int i = 0; i < numPlayers; i++) {
        cout << "Player " << (i+1) << ", please input your name: "; 
        cin >> pName;
        Player p(pName, defaultPtns);
        players.push_back(p);
    }

    return players;    
}


int main()
{
    std::cout << "----------------------" << std::endl;
    std::cout << "\n6Nimmt (Take-6)\n" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::list<Player> players = setupPlayers();

    // Create the board, the cardBank, and the deck of cards
    Board gameBoard;          
    std::list<std::pair<Card,Player*> > cardBank; 
    Deck<Card> gameDeck= createDeck();  

    // Main while loop
    // The game ends when the player with the lowest points reaches 0 points
    while (players.front().getPoints()>0) {    
        Deck<Card> gameDeck= createDeck(); 

        // Shuffle the deck                       
        gameDeck.shuffleDeck(1234); 
        
        // Clear the game board
        ~gameBoard; 
    
        // Load a card into every row of the gameBoard
        gameBoard << --gameDeck;
        gameBoard << --gameDeck;
        gameBoard << --gameDeck;
        gameBoard << --gameDeck;
        
        // Deal 10 cards to each player
        for (int i=0; i<10; i++) {
            for (Player& p : players)
                p+= --gameDeck;
        }

        // Loop until a player no longer has cards
        while (!players.front()) {
            
            // Empty the card bank and print the current state of the board
            cardBank.clear();
            std::cout << gameBoard;
            
            // Ask each player to request a card
            for (Player& p: players) {
                auto choice= std::make_pair(requestCard(p),&p);        
                cardBank.push_back(choice);
            }

            // Sort the cardBank and start with the smallest card
            cardBank.sort();

            // For each card/player pair in the bank
            for (auto cpPair : cardBank)  {

                // Load the card of the cpPair into the gameBoard and store the result of the operation
                std::pair<std::vector<Card>,bool> opResult = (gameBoard << cpPair.first);
                                             
                // If the operation was not successful, ask the player to clear one of the rows
                if (!opResult.second) {
                    int r= requestRow(cpPair.second);           
                    opResult= (gameBoard[r] << cpPair.first);           
                }

                // The player loses points based on the number of cards they have to pick up
                for (Card c : opResult.first)
                    *(cpPair.second)-= *c;

                cout << gameBoard;
            }
            
            // Print the score
            players.sort();
            for (auto p: players)
                std::cout << p << std::endl;
        }
    }

    return 0;
}