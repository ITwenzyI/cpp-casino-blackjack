#ifndef GAME_BLACKJACK_GAME_HPP
#define GAME_BLACKJACK_GAME_HPP

#include <string>
#include <utility>
#include <vector>

#include "domain/Card.hpp"
#include "game/BlackjackRound.hpp"

class ConsoleRenderer;

namespace game {

class BlackjackGame {
 public:
  void run();

 private:
  void showBlackjackMenu();
  void showRules();
  void playRound();
  bool nextCardPlayer(BlackjackRound& round, const std::string& playerName, int& playerHandValue);
  void buildHandPlayer(const domain::Card& card);
  void buildHandDealer(const domain::Card& card);
  void clearRenderedHands();

  std::vector<std::pair<std::string, std::string>> playerRenderedHand_;
  std::vector<std::pair<std::string, std::string>> dealerRenderedHand_;
};

} // namespace game

#endif
