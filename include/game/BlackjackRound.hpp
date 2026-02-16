#ifndef GAME_BLACKJACK_ROUND_HPP
#define GAME_BLACKJACK_ROUND_HPP

#include "domain/Deck.hpp"
#include "domain/Hand.hpp"
#include <vector>

namespace game {

enum class RoundResult {
    Invalid = 0,
    DealerWins,
    PlayerWins,
    BothBust,
    Push
};

class BlackjackRound {
  public:
    // Initializes a new round (deck reset/shuffle, initial dealing).
    void start();
    // Player draws one card and returns it for UI rendering.
    domain::Card playerHit();
    // Marks the player decision "stand" (currently documentary).
    void playerStand();
    // Executes dealer turn using the "<17 draw" rule.
    std::vector<domain::Card> playDealerTurn();

    const domain::Hand& playerHand() const;
    const domain::Hand& dealerHand() const;
    int playerValue() const;
    int dealerValue() const;
    bool playerHasBlackjack() const;
    // Returns a typed round result for clearer game flow and debugging.
    RoundResult evaluateResult() const;

  private:
    domain::Deck deck_;
    domain::Hand playerHand_;
    domain::Hand dealerHand_;
    bool playerStands_ = false;
};

} // namespace game

#endif
