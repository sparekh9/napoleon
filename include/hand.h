#include <iostream>
#include <unordered_set>
#include <deck.h>

namespace napoleon {

  class Hand {

    public:

      Hand(unordered_set<card_t> hand);

      //Returns false if card exists in hand or insert failed, true otherwise
      bool Insert(card_t card);

      //Returns false if card is not in hand or remove failed, true otherwise
      bool Remove(card_t card);

      void PrintHand();

    private:

      std::unordered_set<card_t> hand_;
  };
}