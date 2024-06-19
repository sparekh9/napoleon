#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <numeric>
#include <enet/enet.h>
#include "../include/hand.h"

namespace napoleon {

  typedef std::pair<card_t, int> move_t;

  class Player{
    public:

    Player(int clientSocket, string user) : clientSocket_(clientSocket), user_(user) { }

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

    int GetSocket() {
      return clientSocket_;
    }

    move_t RequestMove(vector<Player> players);

    void PrintHand() {
      hand_.PrintHand();
    }

    private:
      int clientSocket_ = -1;
      string user_;
      Hand hand_;
  };
}