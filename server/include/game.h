#include "../include/player.h"
#include <iostream>
#include <vector>
#include <string> 
#include <netinet/in.h> 
#include <sys/socket.h> 


using namespace std;

namespace napoleon {

  class Game {
        
    public:

      Game(std::string code) : code_(code) {};

      void SetTarget(int tgt) { tgt_ = tgt; }

      bool Ready() { return players_.size() == tgt_; }

      void AddPlayer(Player player);

      bool ValidUsr(std::string username);

      void Init();

      void Run();

      void PrintGame();

      void BroadcastExc(const char *msg, Player player);

      void Broadcast(const char *msg);

    private:

      const std::string code_;
      int tgt_ = -1;
      int n_ = 0;
      int starter_;
      vector<Player> players_{};
  };
}