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

    // Builds a fresh 52-card deck in a defined order.
    void reset();
    // Shuffles the deck and resets the draw index.
    void shuffle();
    // Draws the next card; when empty, the deck is rebuilt and shuffled automatically.
    Card draw();

  private:
    std::vector<Card> cards_;
    std::size_t nextIndex_;
    std::mt19937 rng_;
};

} // namespace domain

#endif
