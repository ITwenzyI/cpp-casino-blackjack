#ifndef DOMAIN_CARD_HPP
#define DOMAIN_CARD_HPP

#include <string>

namespace domain {

enum class Suit { Spades, Hearts, Diamonds, Clubs };

class Card {
  public:
    // rank: 2-14 (11=K, 12=D, 13=J, 14=A)
    Card(int rank, Suit suit);

    int rank() const;
    Suit suit() const;
    // Blackjack value: face cards=10, ace defaults to 11
    int blackjackValue() const;
    // Returns short rank text for renderer output (e.g. "A", "10")
    std::string rankText() const;
    // Returns suit as symbol string
    std::string suitText() const;

  private:
    int rank_;
    Suit suit_;
};

} // namespace domain

#endif
