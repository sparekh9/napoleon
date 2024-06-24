#include "../include/deck.h"
#include <ctime>

using namespace std;

namespace napoleon {

  string suits[4] = {"♣", "♡", "♢", "♠"};

  int GetCard(int rank, int suit) {
    return suit * 13 + (rank - 1);
  }

  int GetRank(card_t card) {
    return card % 13 + 1;
  }

  int GetSuit(card_t card) {
    return card / 13;
  }

  string GetCardString(card_t card) {
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
  
  Deck::Deck(bool shuffle) {
    auto begin = deck_.begin();
    begin++;
    std::iota(begin, deck_.end(), 1);
    if (shuffle){
      srand((unsigned) time(NULL));
      int reps = rand() % 100;
      Shuffle(reps);
    }
  }

  // Implementation of Fisher-Yates Shuffle
  void Deck::Shuffle(int n) {
    for (int count = 0; count < n; count++) {
      for (int i = deck_.size() - 1; i > 0; i--) {
        srand((unsigned) time(NULL));
        int j = rand() % i;
        deck_[i] = deck_[i] + deck_[j];
        deck_[j] = deck_[i] - deck_[j];
        deck_[i] = deck_[i] - deck_[j];
      }
    }
  }

  bool Deck::IsEmpty() {
    return deck_.empty();
  }

  int Deck::Draw() {
    int last = deck_.back();
    deck_.pop_back();
    return last;
  }

  void Deck::PrintDeck(){
    for (int i = 0; i < 52; i++) {
      cout << GetCardString(deck_[i]) << " ";
      if ((i + 1) % 13 == 0) {
        cout << "\n";
      }
    }
  }
}

