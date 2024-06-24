#include "../include/game.h"

using namespace std;

namespace napoleon {

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

  bool Game::ValidUsr(std::string username) {
    std::cout << "Validating " << username << "\n";
    for (Player player : players_) {
      if (player.GetUser().compare(username) == 0) {
        return false;
      }
    }
    return true;
  }

  void Game::AddPlayer(Player player) {
    if (n_ > 0) {
      char broadcast[1024] = {'\0'};
      sprintf(broadcast, "2|%s joined the game!", player.GetUser().c_str());
      Broadcast(broadcast); 
    }

    players_.push_back(player);
    n_++;

    char conf_msg[1024] = {'\0'};
    int len_msg = sprintf(conf_msg, "2|Added to game (CODE:%s)", code_.c_str());

    // std::cout << "Sending new player " << conf_msg << "\n";
    if (n_ > 1) {
      len_msg += sprintf(conf_msg + len_msg, "\nCurrent Players in game:");
      for (int i = 0; i < n_ - 1; i++) {
        len_msg += sprintf(conf_msg + len_msg, "\n%d. %s", (i + 1), players_[i].GetUser().c_str());
      }
    }
    std::cout << "Sending " << conf_msg << "\n";
    if (!player.SendMessage(conf_msg)) {
      printf("Could not send message to %s\n", player.GetUser().c_str());
    }
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

  void Game::Broadcast(const char *msg) {
    for (Player player : players_) {
      player.SendMessage(msg);
    }
  }

  void Game::BroadcastExc(const char *msg, Player player) {
    for (Player curr_player : players_) {
      if (curr_player != player) {
        player.SendMessage(msg);
      }
    }
  }
}