#include <iostream>
#include <array>
#include <cstring>
#include <string>
#include <vector>
#include <numeric>
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include "../include/hand.h"

namespace napoleon {

  typedef std::pair<card_t, int> move_t;

  class Player{
    public:

    bool operator!= (Player oth) {
      return this->user_.compare(oth.GetUser()) != 0;
    }

    Player(int clientSocket, string user) {
      clientSocket_ = clientSocket;
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

    int GetSocket() {
      return clientSocket_;
    }

    bool SendMessage(const char *msg) {
      return send(clientSocket_, msg, strlen(msg), 0) > 0;
    }

    move_t RequestMove(vector<Player> players);

    std::string PrintHand() {
      return hand_.PrintHand();
    }

    private:
      int clientSocket_ = -1;
      string user_;
      Hand hand_;
  };
}