#include "../include/hand.h"

using namespace std;

namespace napoleon {

  Hand::Hand(unordered_set<card_t> hand) {
    if (hand == nullptr) {
      hand_ = unordered_set<card_t>(0);
    }
    else {
      hand_ = hand;
    }
  }

  bool Hand::Insert(card_t card) {
    if (hand_.contains(card)) {
      return false;
    }
    hand_.insert(card);
  }

  bool Hand::Remove(card_t card) {
    if (!hand_.contains(card)) {
      return false;
    }
    hand_.remove(card);
  }

  void Hand::PrintHand() {
    for (auto const &card : hand_) {
      Deck::GetString(card);
    }
  }
}