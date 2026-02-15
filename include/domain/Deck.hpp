#ifndef DOMAIN_DECK_HPP
#define DOMAIN_DECK_HPP

#include "domain/Card.hpp"
#include <cstddef>
#include <random>
#include <vector>

namespace domain {

class Deck {
  public:
    Deck();

    // Baut ein frisches 52er-Deck in definierter Reihenfolge auf.
    void reset();
    // Mischt das Deck und setzt den Zieh-Index zurück.
    void shuffle();
    // Zieht die nächste Karte, bei leerem Deck wird automatisch neu gemischt.
    Card draw();

  private:
    std::vector<Card> cards_;
    std::size_t nextIndex_;
    std::mt19937 rng_;
};

} // namespace domain

#endif
