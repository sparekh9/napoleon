#include "../include/game.h"

using namespace std;

namespace napoleon {

  // Game::Game(int n) {
  //   n_ = n;
  //   for (int i = 0; i < n; i++) {
  //     players_.push_back(Player("Player " + to_string(i)));
  //   }
  // }

  // Game::Game(vector<string> players) {
  //   for (int i = 0; i < players.size(); i++) {
  //     players_.push_back(Player(players[i]));
  //   }
  //   n_ = players_.size();
  // }

  void Game::Init() {
    Deck deck = Deck(true);
    int p = 0;
    while (!deck.IsEmpty()) {
      card_t card = deck.Draw();
      if (card == ACE_OF_SPADES) {
        starter_ = p;
      }
      players_[p++].Insert(card);
      if (p >= n_) {
        p = 0;
      }
    }
  }

  void Game::AddPlayer(Player player) {
    players_.push_back(player);
    n_++;
  }

  void Game::Run() {
    cout << "Welcome to Napoleon!\n";
    Player curr_player = players_[starter_];
    cout << players_[starter_].GetUser() << " has the A♠ and will start.\n";
    while (true) {
      move_t move = curr_player.RequestMove(players_);
      
    }
  }

  void Game::PrintGame() {
    for (int i = 0; i < n_; i++) {
      cout << players_[i].GetUser() << "'s Hand: ";
      players_[i].PrintHand();
    }
  }
}