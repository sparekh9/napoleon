#include "../include/player.h"
#include <cstring>

using namespace std;

namespace napoleon {

  move_t Player::RequestMove(vector<Player> players) {
    cout << "It's your turn!, here is your hand:\n";
    PrintHand();
    cout << "What card would you like to request?\n";
    int rank = -1;
    while (rank == -1 || !hand_.IsValidMove(rank)) {
      cout << "Pick a rank (2 - 10, or A, J, Q, K):\n";
      string rank_string;
      cin >> rank_string;
      try {
        rank = stoi(rank_string);
        if (rank < 2 || rank > 10) {
          cout << "Invalid rank. ";
          rank = -1;
        }
      }
      catch (const exception& e) {
        switch (rank_string[0]) {
          case 'A': rank = 1;
          break;
          case 'J': rank = 11;
          break;
          case 'Q': rank = 12;
          break;
          case 'K': rank = 13;
          break;
          default: cout << "Invalid rank. ";
        }
      }
      if (rank != -1 && !hand_.IsValidMove(rank)) {
        cout << "You cannot ask for that card since you do not have any cards of that rank.\n";
      }
    }
    int suit = -1;
    while (suit == -1) {
      cout << "Pick a suit (1 - ♣, 2 - ♡, 3 - ♢, 4 - ♠):\n";
      cin >> suit;
      if (suit < -1 || suit > 4) {
        suit = -1;
        cout << "Invalid suit. ";
      }
    }
    card_t card = GetCard(rank, --suit);
    int i;
    bool found = false;
    while (!found) {
      cout << "Pick a player to ask for " + GetCardString(card) + " (type number next to username):\n";
      for (int i = 0; i < players.size(); i++) {
        if (user_.compare(players[i].GetUser()) != 0) {
          cout << (i + 1) << ". " << players[i].GetUser() << "\n";
        }
      }
       cin >> i;
      if (i >= 0 && i < players.size()) {
        found = true;
      }
    }
    return make_pair(card, i);
  }
}