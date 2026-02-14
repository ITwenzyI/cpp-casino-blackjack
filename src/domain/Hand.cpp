#include "domain/Hand.hpp"

namespace domain {

void Hand::clear() {
  cards_.clear();
}

void Hand::addCard(const Card& card) {
  cards_.push_back(card);
}

int Hand::value() const {
  int total = 0;
  int aces = 0;

  for (const Card& card : cards_) {
    total += card.blackjackValue();
    if (card.rank() == 14) {
      ++aces;
    }
  }

  while (total > 21 && aces > 0) {
    total -= 10;
    --aces;
  }

  return total;
}

bool Hand::isBlackjack() const {
  return cards_.size() == 2 && value() == 21;
}

const std::vector<Card>& Hand::cards() const {
  return cards_;
}

} // namespace domain
