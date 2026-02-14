#ifndef DOMAIN_HAND_HPP
#define DOMAIN_HAND_HPP

#include <vector>
#include "domain/Card.hpp"

namespace domain {

class Hand {
 public:
  void clear();
  void addCard(const Card& card);
  int value() const;
  bool isBlackjack() const;
  const std::vector<Card>& cards() const;

 private:
  std::vector<Card> cards_;
};

} // namespace domain

#endif
