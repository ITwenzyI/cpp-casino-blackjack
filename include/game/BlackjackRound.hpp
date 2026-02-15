#ifndef GAME_BLACKJACK_ROUND_HPP
#define GAME_BLACKJACK_ROUND_HPP

#include "domain/Deck.hpp"
#include "domain/Hand.hpp"
#include <vector>

namespace game {

class BlackjackRound {
  public:
    // Initialisiert eine neue Runde (Deck reset/shuffle, erste Karten verteilen).
    void start();
    // Spieler zieht eine Karte und erhaelt sie für die UI zurück.
    domain::Card playerHit();
    // Markiert die Spielerentscheidung "Stand" (aktuell dokumentarisch).
    void playerStand();
    // Führt Dealer-Zug gemäss Regel "<17 ziehen" aus.
    std::vector<domain::Card> playDealerTurn();

    const domain::Hand& playerHand() const;
    const domain::Hand& dealerHand() const;
    int playerValue() const;
    int dealerValue() const;
    bool playerHasBlackjack() const;
    // 1=Dealer gewinnt, 2=Spieler gewinnt, 3=beide bust, 4=Push, 0=Fehlerfall
    int evaluateResult() const;

  private:
    domain::Deck deck_;
    domain::Hand playerHand_;
    domain::Hand dealerHand_;
    bool playerStands_ = false;
};

} // namespace game

#endif
