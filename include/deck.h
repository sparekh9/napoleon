#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <numeric>
#include <cstdlib> 
#include <sstream>

using namespace std;

#define ACE_OF_SPADES 39

namespace napoleon {

  typedef int card_t;
  
  class Deck {

    public:

      Deck(bool shuffle);

      // Implementation of Fisher-Yates Shuffle
      void Shuffle(int n);

      bool IsEmpty();

      //Draw the card from the top
      card_t Draw();

      //Print all remaining cards in the deck
      void PrintDeck();

    private:
    
      vector<int> deck_{vector<card_t>(52, 0)};
  };

  int GetCard(int rank, int suit);

  int GetRank(card_t card);

  int GetSuit(card_t card);

  string GetCardString(card_t card);
}