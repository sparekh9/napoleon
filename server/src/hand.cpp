#include "../include/hand.h"

using namespace std;

namespace napoleon {

  Hand::Hand() {
    unordered_set<card_t> hand;
    hand_ = hand;
  }

  Hand::Hand(unordered_set<card_t> hand) {
    hand_ = hand;
  }

  bool Hand::Insert(card_t card) {
    if (hand_.count(card) > 0) {
      return false;
    }
    hand_.insert(card);
    int rank = GetRank(card);
    if (ranks_.count(rank) == 0) {
      ranks_.insert(make_pair(rank, 1));
    } 
    else {
      ranks_[card]++;
    }
    return true;
  }

  bool Hand::Remove(card_t card) {
    if (hand_.count(card) == 0) {
      return false;
    }
    hand_.erase(card);
    if (ranks_[card] == 1) {
      ranks_.erase(card);
    }
    else {
      ranks_[card]--;
    }
    return true;
  }

  bool Hand::IsValidMove(int rank) {
    return ranks_.count(rank) != 0;
  }

  std::string Hand::PrintHand() {
    std::stringstream out;
    for (auto const &card : hand_) {
      out << GetCardString(card) << "\t";
    }
    out << "\n";
    return out.str();
  }
}