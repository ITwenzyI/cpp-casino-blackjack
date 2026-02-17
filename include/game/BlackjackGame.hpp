#ifndef GAME_BLACKJACK_GAME_HPP
#define GAME_BLACKJACK_GAME_HPP

#include <string>
#include <utility>
#include <vector>

#include "domain/Card.hpp"
#include "game/BlackjackRound.hpp"
#include "ui/ConsoleInput.hpp"
#include "ui/ConsoleOutput.hpp"
#include "ui/GamePacer.hpp"

namespace game {

class BlackjackGame {
  public:
    // Entry point for the full console game flow.
    void run();

  private:
    void showBlackjackMenu();
    void configurePacing();
    void showRules();
    void playRound();
    bool nextCardPlayer(BlackjackRound& round, const std::string& playerName, int& playerHandValue);
    void buildHandPlayer(const domain::Card& card);
    void buildHandDealer(const domain::Card& card);
    void clearRenderedHands();

    std::vector<std::pair<std::string, std::string>> playerRenderedHand_;
    std::vector<std::pair<std::string, std::string>> dealerRenderedHand_;
    // Central input adapter so game logic does not use std::cin directly.
    ConsoleInput input_;
    // Central output adapter so game logic does not use std::cout directly.
    ConsoleOutput output_;
    // Central pacing component to control round flow timing.
    ui::GamePacer pacer_;
};

} // namespace game

#endif
