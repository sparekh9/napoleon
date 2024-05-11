#include "../include/deck_.h"

using namespace std;

namespace napoleon {
  
  deck_::deck_(bool shuffle) {
    auto begin = deck_.begin();
    begin++;
    std::iota(begin, deck_.end(), 1);
    if (shuffle){
      Shuffle();
    }
  }

  // Implementation of Fisher-Yates Shuffle
  void deck_::Shuffle() {
    for (int i = deck_.size() - 1; i > 0; i--) {
      int j = rand() % i;
      deck_[i] = deck_[i] + deck_[j];
      deck_[j] = deck_[i] - deck_[j];
      deck_[i] = deck_[i] - deck_[j];
    }
  }

  int deck_::Draw() {
    int last = deck_.back();
    deck_.pop_back();
    return last;
  }

  void deck_::Printdeck_(){
    for (int i = 0; i < 52; i++) {
      cout << GetString(deck_[i]) << " ";
      if ((i + 1) % 13 == 0) {
        cout << "\n";
      }
    }
  }

  int deck_::GetRank(card_t card) {
    return card % 13 + 1;
  }

  int deck_::GetSuit(card_t card) {
    return card / 13;
  }

  string deck_::GetString(card_t card) {
    int rank = GetRank(card);
    int suit = GetSuit(card);

    stringstream val;
    if (rank == 1 || rank > 10) {
      switch (rank) {
        case 1: val << 'A';
        break;
        case 11: val << 'J';
        break;
        case 12: val << 'Q';
        break;
        case 13: val << 'K';
        break;
      }
    }
    else {
      val << rank;
    }
    val << suits[suit];
    return val.str();
  }
}

