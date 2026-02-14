#ifndef GAME_BLACKJACK_ROUND_HPP
#define GAME_BLACKJACK_ROUND_HPP

#include <vector>
#include "domain/Deck.hpp"
#include "domain/Hand.hpp"

namespace game {

class BlackjackRound {
 public:
  void start();
  domain::Card playerHit();
  void playerStand();
  std::vector<domain::Card> playDealerTurn();

  const domain::Hand& playerHand() const;
  const domain::Hand& dealerHand() const;
  int playerValue() const;
  int dealerValue() const;
  bool playerHasBlackjack() const;
  int evaluateResult() const;

 private:
  domain::Deck deck_;
  domain::Hand playerHand_;
  domain::Hand dealerHand_;
  bool playerStands_ = false;
};

} // namespace game

#endif
