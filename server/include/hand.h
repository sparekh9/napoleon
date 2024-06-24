#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include "../include/deck.h"

namespace napoleon {

  class Hand {

    public:

      Hand();

      Hand(unordered_set<card_t> hand);

      //Returns false if card exists in hand or insert failed, true otherwise
      bool Insert(card_t card);

      //Returns false if card is not in hand or remove failed, true otherwise
      bool Remove(card_t card);

      //Checks if player has the rank they are asking for
      bool IsValidMove(int rank);

      std::string PrintHand();

    private:
      std::unordered_map<int, size_t> ranks_;
      std::unordered_set<card_t> hand_;
  };
}