#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <numeric>
#include <cstdlib> 
#include <sstream>

using namespace std;

namespace napoleon {

  typedef int card_t;

  // enum suit {clubs, hearts, diamonds, spades};
  
  class Deck {
    friend class Hand;

    public:

      Deck(bool shuffle);

      // Implementation of Fisher-Yates Shuffle
      void Shuffle();

      //Draw the card from the top
      card_t Draw();

      //Return the readable string for the card
      string GetString(card_t card);

      //Print all remaining cards in the deck
      void PrintDeck();

    private:

      int GetRank(card_t card);
      int GetSuit(card_t card);
      
      vector<int> deck_{vector<card_t>(52, 0)};
      array<string, 4> suits = {"♣", "♡", "♢", "♠"};
  };
}