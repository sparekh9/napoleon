#include "../include/deck.h"
#include "../include/player.h"
#include <iostream>

using namespace std;
using namespace napoleon;

int main() {

  Deck deck = Deck(true);
  deck.PrintDeck();
  cout << "\n";
  for (int i = 0; i < 52; i++) {
    cout << deck.GetString(deck.Draw()) + " ";
    if ((i + 1) % 13 == 0) {
      cout << "\n";
    }
  }
  return 0;
}