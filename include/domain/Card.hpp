#ifndef DOMAIN_CARD_HPP
#define DOMAIN_CARD_HPP

#include <string>

namespace domain {

enum class Suit { Spades, Hearts, Diamonds, Clubs };

class Card {
  public:
    Card(int rank, Suit suit);

    int rank() const;
    Suit suit() const;
    int blackjackValue() const;
    std::string rankText() const;
    std::string suitText() const;

  private:
    int rank_;
    Suit suit_;
};

} // namespace domain

#endif
