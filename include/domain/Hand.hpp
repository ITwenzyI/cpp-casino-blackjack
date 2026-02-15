#ifndef DOMAIN_HAND_HPP
#define DOMAIN_HAND_HPP

#include "domain/Card.hpp"
#include <vector>

namespace domain {

class Hand {
  public:
    void clear();
    void addCard(const Card& card);
    // Calculates current blackjack value including ace correction (11 -> 1).
    int value() const;
    // True only for exactly two cards with value 21.
    bool isBlackjack() const;
    // Read-only access for rendering and game logic.
    const std::vector<Card>& cards() const;

  private:
    std::vector<Card> cards_;
};

} // namespace domain

#endif
