#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <numeric>
#include <deck.h>
#include <hand.h>


namespace napoleon {

  class Player{
    public:

    Player(string user, Hand hand) user_(user), hand_(hand){}

    void Insert(card_t card) {
      hand_.Insert(card);
    }

    void Remove(card_t card) {
      hand_.Remove(card);
    }

    void PrintHand();

    private:

      string user_;

      Hand hand_;
  };
}