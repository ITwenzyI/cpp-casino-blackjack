#ifndef DOMAIN_HAND_HPP
#define DOMAIN_HAND_HPP

#include "domain/Card.hpp"
#include <vector>

namespace domain {

class Hand {
  public:
    void clear();
    void addCard(const Card& card);
    // Berechnet den aktuellen Blackjack-Wert inkl. Ass-Korrektur (11 -> 1).
    int value() const;
    // True nur bei exakt zwei Karten mit Wert 21.
    bool isBlackjack() const;
    // Read-only Zugriff für Anzeige- und Spiellogik.
    const std::vector<Card>& cards() const;

  private:
    std::vector<Card> cards_;
};

} // namespace domain

#endif
