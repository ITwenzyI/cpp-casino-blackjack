#ifndef UI_CONSOLE_OUTPUT_HPP
#define UI_CONSOLE_OUTPUT_HPP

#include <string>
#include "game/BlackjackRound.hpp"

class ConsoleOutput {
  public:
    void showCasinoMenu() const;
    void showGameSelectionMenu() const;
    void showBlackjackMenu() const;
    void showInvalidChoice() const;

    void showWelcome(const std::string& playerName) const;
    void showGameStarting() const;
    void showSeparator() const;

    void showDealerStartHand() const;
    void showDealerVisualHand() const;
    void showDealerHandValue(int handValue) const;
    void showNoMoreDealerCards() const;

    void showPlayerVisualHand(const std::string& playerName) const;
    void showPlayerHandValue(const std::string& playerName, int handValue) const;
    void showPlayerBlackjack(const std::string& playerName) const;
    void showBlackjackPayout(const std::string& playerName) const;
    void showHitPrompt() const;
    void showPlayerBust(const std::string& playerName) const;

    void showRoundResult(game::RoundResult resultCode, const std::string& playerName,
        int playerValue, int dealerValue) const;
    void showSatisfactionPrompt() const;
    void showRules() const;

    void showError() const;
};

#endif
