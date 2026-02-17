#include "ui/ConsoleOutput.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib>

namespace {
const char* paceModeText(const ui::PaceMode mode) {
    switch (mode) {
        case ui::PaceMode::Instant:
            return "Instant";
        case ui::PaceMode::Smooth:
            return "Smooth";
        case ui::PaceMode::Cinematic:
            return "Cinematic";
        default:
            return "Unknown";
    }
}

std::string handValueText(const int value) {
    if (value < 0) {
        return "--";
    }
    return std::to_string(value);
}

std::string joinCards(const std::vector<std::string>& cards) {
    if (cards.empty()) {
        return "-";
    }

    std::ostringstream out;
    for (std::size_t i = 0; i < cards.size(); ++i) {
        if (i > 0) {
            out << " ";
        }
        out << cards[i];
    }
    return out.str();
}

std::pair<std::string, std::string> resultAndPayoutText(
    const game::RoundResult resultCode, const std::string& playerName) {
    switch (resultCode) {
        case game::RoundResult::DealerWins:
            return {"Dealer wins", playerName + " loses the stake."};
        case game::RoundResult::PlayerWins:
            return {"Player wins", playerName + " receives 2x the stake back."};
        case game::RoundResult::BothBust:
            return {"Both bust", "No one wins. " + playerName + " loses the stake."};
        case game::RoundResult::Push:
            return {"Push", playerName + " gets the stake back."};
        case game::RoundResult::Invalid:
        default:
            return {"Invalid result", "Result state could not be evaluated."};
    }
}
} // namespace

void ConsoleOutput::clearScreen() const {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void ConsoleOutput::showSection(const std::string& title) const {
    std::cout << std::endl;
    std::cout << "|====| " << title << " |====|" << std::endl;
}

void ConsoleOutput::showCasinoMenu() const {
    std::cout << "|====| Deluxe Casino |====|" << std::endl;
    std::cout << "1. Game Selection" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Your Choice:" << std::endl;
}

void ConsoleOutput::showGameSelectionMenu() const {
    std::cout << "|====| Game Selection |====|" << std::endl;
    std::cout << "-|- Card Games -|-" << std::endl;
    std::cout << "1. Blackjack" << std::endl;
    std::cout << "Your Choice:" << std::endl;
}

void ConsoleOutput::showBlackjackMenu() const {
    std::cout << "|====| Main Menu |====|" << std::endl;
    std::cout << "1. Start Game" << std::endl;
    std::cout << "2. Rules" << std::endl;
    std::cout << "3. Pacing" << std::endl;
    std::cout << "4. Back" << std::endl;
}

void ConsoleOutput::showPacingMenu(const ui::PaceMode currentMode) const {
    std::cout << "|====| Pacing Settings |====|" << std::endl;
    std::cout << "Current mode: " << paceModeText(currentMode) << std::endl;
    std::cout << "1. Instant" << std::endl;
    std::cout << "2. Smooth" << std::endl;
    std::cout << "3. Cinematic" << std::endl;
    std::cout << "4. Back" << std::endl;
    std::cout << "Your Choice:" << std::endl;
}

void ConsoleOutput::showPacingUpdated(const ui::PaceMode mode) const {
    std::cout << "Pacing mode set to: " << paceModeText(mode) << std::endl;
}

void ConsoleOutput::showInvalidChoice() const {
    std::cout << "Invalid choice" << std::endl;
}

void ConsoleOutput::promptUsername() const {
    std::cout << "Enter your username: " << std::endl;
}

void ConsoleOutput::showWelcome(const std::string& playerName) const {
    std::cout << "Welcome to Blackjack " << playerName << std::endl;
}

void ConsoleOutput::showGameStarting() const {
    std::cout << "The game is starting..." << std::endl;
}

void ConsoleOutput::showSeparator() const {
    std::cout << "----------------------------------------------------------" << std::endl;
}

void ConsoleOutput::showDrawingCard() const {
    std::cout << "Drawing card..." << std::endl;
}

void ConsoleOutput::showDealerStartHand() const {
    std::cout << "Dealer starting hand:" << std::endl;
}

void ConsoleOutput::showDealerDrawsCard() const {
    std::cout << "Dealer draws a card." << std::endl;
}

void ConsoleOutput::showDealerVisualHand() const {
    std::cout << "Dealer visual hand:" << std::endl;
}

void ConsoleOutput::showDealerHandValue(const int handValue) const {
    std::cout << "Dealer hand value: " << handValue << std::endl;
}

void ConsoleOutput::showNoMoreDealerCards() const {
    std::cout << "Dealer draws no more cards!" << std::endl;
}

void ConsoleOutput::showPlayerVisualHand(const std::string& playerName) const {
    std::cout << playerName << "'s visual hand:" << std::endl;
}

void ConsoleOutput::showPlayerDrawsCard(const std::string& playerName) const {
    std::cout << playerName << " draws a card." << std::endl;
}

void ConsoleOutput::showPlayerHandValue(const std::string& playerName, const int handValue) const {
    std::cout << playerName << " hand value: " << handValue << std::endl;
}

void ConsoleOutput::showPlayerBlackjack(const std::string& playerName) const {
    std::cout << playerName << " has BLACKJACK!" << std::endl;
}

void ConsoleOutput::showBlackjackPayout(const std::string& playerName) const {
    std::cout << playerName
              << " wins automatically with blackjack and receives 1.5x the stake back."
              << std::endl;
}

void ConsoleOutput::showHitPrompt() const {
    std::cout << "Do you want to take another card (yes/no or h/s)?" << std::endl;
}

void ConsoleOutput::showInvalidYesNo() const {
    std::cout << "Invalid input. Please enter yes or no." << std::endl;
}

void ConsoleOutput::showPlayerBust(const std::string& playerName) const {
    std::cout << playerName << " ... You are over 21..." << std::endl;
}

void ConsoleOutput::showRoundHud(const std::string& playerName, const int playerValue,
    const int dealerVisibleValue, const ui::PaceMode paceMode) const {
    std::cout << "[HUD] " << playerName << ": " << handValueText(playerValue)
              << " | Dealer (visible): " << handValueText(dealerVisibleValue)
              << " | Pace: " << paceModeText(paceMode) << std::endl;
}

void ConsoleOutput::showRoundResult(const game::RoundResult resultCode,
    const std::string& playerName, const int playerValue, const int dealerValue) const {
    std::cout << std::endl;
    switch (resultCode) {
        case game::RoundResult::DealerWins:
            std::cout << "The dealer wins with: " << dealerValue << " points!" << std::endl;
            std::cout << playerName << " loses the stake." << std::endl;
            std::cout << "Better luck next time!" << std::endl;
            break;
        case game::RoundResult::PlayerWins:
            std::cout << playerName << " wins with: " << playerValue << " points!" << std::endl;
            std::cout << playerName << " receives 2x the stake back." << std::endl;
            std::cout << "Congratulations on your win!" << std::endl;
            break;
        case game::RoundResult::BothBust:
            std::cout << playerName << " and the dealer are both over 21!" << std::endl;
            std::cout << "No one wins and " << playerName << " loses the stake!" << std::endl;
            std::cout << "Better luck next time!" << std::endl;
            break;
        case game::RoundResult::Push:
            std::cout << "Tie between " << playerName << " and the dealer with " << playerValue
                      << " points each!" << std::endl;
            std::cout << playerName << " gets the stake back." << std::endl;
            std::cout << "Nice push!" << std::endl;
            break;
        case game::RoundResult::Invalid:
        default:
            showError();
            break;
    }
}

void ConsoleOutput::showRoundSummary(const std::string& playerName,
    const std::vector<std::string>& playerCards, const int playerTotal,
    const std::vector<std::string>& dealerCards, const int dealerTotal,
    const game::RoundResult resultCode) const {
    const auto [resultText, payoutText] = resultAndPayoutText(resultCode, playerName);

    std::cout << std::endl;
    std::cout << "|====| Round Summary |====|" << std::endl;
    std::cout << "Player cards : " << joinCards(playerCards) << std::endl;
    std::cout << "Player total : " << playerTotal << std::endl;
    std::cout << "Dealer cards : " << joinCards(dealerCards) << std::endl;
    std::cout << "Dealer total : " << dealerTotal << std::endl;
    std::cout << "Result       : " << resultText << std::endl;
    std::cout << "Payout       : " << payoutText << std::endl;
}

void ConsoleOutput::showReplayMenu() const {
    std::cout << std::endl;
    std::cout << "|====| Next Action |====|" << std::endl;
    std::cout << "1. Play again" << std::endl;
    std::cout << "2. Back to Blackjack Menu" << std::endl;
    std::cout << "Your Choice:" << std::endl;
}

void ConsoleOutput::showSatisfactionPrompt() const {
    std::cout << std::endl << std::endl;
    std::cout << "Thanks for playing Kilian's Blackjack!" << "\nAre you satisfied?" << std::endl;
}

void ConsoleOutput::showRules() const {
    std::cout << "|====| General Goal |====|" << std::endl;
    std::cout << "1. The goal is to get as close to 21 points as possible." << std::endl;
    std::cout << "2. Anyone with more than 21 points loses automatically (bust)." << std::endl;

    std::cout << std::endl << "|====| Card Values |====|" << std::endl;
    std::cout << "3. Number cards count as their number (e.g. 2-10)." << std::endl;
    std::cout << "4. Jack, Queen, and King count as 10 points." << std::endl;
    std::cout << "5. The Ace counts as 1 or 11, depending on what is better." << std::endl;

    std::cout << std::endl << "|====| Game Flow |====|" << std::endl;
    std::cout << "6. Each player receives two cards at the start." << std::endl;
    std::cout << "7. The player decides whether to draw another card ('Hit') or stop ('Stand')."
              << std::endl;
    std::cout << "8. The goal is to be closer to 21 than the dealer without going over."
              << std::endl;
    std::cout << "9. Blackjack is an Ace plus a 10-value card in the first two cards." << std::endl;

    std::cout << std::endl << "|====| Dealer Rules |====|" << std::endl;
    std::cout << "10. The dealer plays last." << std::endl;
    std::cout << "11. The dealer must draw at 16 or lower." << std::endl;
    std::cout << "12. The dealer must stand at 17 or higher." << std::endl;

    std::cout << std::endl << "|====| Win & Loss |====|" << std::endl;
    std::cout << "13. Whoever is closer to 21 than the dealer wins." << std::endl;
    std::cout << "14. In a tie, the stake is returned." << std::endl;
    std::cout << "===============================" << std::endl;
}

void ConsoleOutput::showError() const {
    std::cerr << "Error!" << std::endl;
}
