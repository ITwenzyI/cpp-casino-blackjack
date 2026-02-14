#include "domain/Deck.hpp"

#include <algorithm>

namespace domain {

Deck::Deck() : nextIndex_(0), rng_(std::random_device{}()) {
  reset();
}

void Deck::reset() {
  cards_.clear();
  cards_.reserve(52);

  for (const Suit suit : {Suit::Spades, Suit::Hearts, Suit::Diamonds, Suit::Clubs}) {
    for (int rank = 2; rank <= 14; ++rank) {
      cards_.emplace_back(rank, suit);
    }
  }

  nextIndex_ = 0;
}

void Deck::shuffle() {
  std::shuffle(cards_.begin(), cards_.end(), rng_);
  nextIndex_ = 0;
}

Card Deck::draw() {
  if (nextIndex_ >= cards_.size()) {
    reset();
    shuffle();
  }
  return cards_[nextIndex_++];
}

} // namespace domain
