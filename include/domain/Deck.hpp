#ifndef DOMAIN_DECK_HPP
#define DOMAIN_DECK_HPP

#include <cstddef>
#include <random>
#include <vector>
#include "domain/Card.hpp"

namespace domain {

class Deck {
 public:
  Deck();

  void reset();
  void shuffle();
  Card draw();

 private:
  std::vector<Card> cards_;
  std::size_t nextIndex_;
  std::mt19937 rng_;
};

} // namespace domain

#endif
