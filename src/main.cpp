#include "../include/game.h"
#include <iostream>

using namespace std;
using namespace napoleon;

int main() {
  Game game = Game(4);
  game.Init();
  // game.PrintGame();
  game.Run();
  return 0;
}