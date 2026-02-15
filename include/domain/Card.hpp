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
    // Blackjack-Wert: Bildkarten=10, Ass standardmässig=11
    int blackjackValue() const;
    // Ausgabe kürzer Kartenranks für Renderer (z.B. "A", "10")
    std::string rankText() const;
    // Gibt Suit als Symbolstring zurück
    std::string suitText() const;

  private:
    int rank_;
    Suit suit_;
};

} // namespace domain

#endif
