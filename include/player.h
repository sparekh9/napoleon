#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <numeric>
#include "../include/hand.h"

namespace napoleon {

  typedef std::pair<card_t, int> move_t;

  class Player{
    public:

    Player(string user) {
      user_ = user;
    }

    Player(string user, Hand hand) {
      user_ = user;
      hand_ = hand;
    }

    void Insert(card_t card) {
      hand_.Insert(card);
    }

    void Remove(card_t card) {
      hand_.Remove(card);
    }

    string GetUser() {
      return user_;
    }

    move_t RequestMove(vector<Player> players);

    void PrintHand() {
      hand_.PrintHand();
    }

    private:

      string user_;
      Hand hand_;
  };
}