#include "../include/player.h"
#include <iostream>
#include <vector>
#include <string> 


using namespace std;

namespace napoleon {

  class Game {
        
    public:

      Game() {};

      // Game(int n);

      // Game(vector<string> players);

      void AddPlayer(Player player);

      void Wait();

      void Init();

      void Run();

      void PrintGame();

    private:

      int n_ = 0;

      int starter_;

      vector<Player> players_{};
  };
}