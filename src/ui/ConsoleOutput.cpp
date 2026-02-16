#include "ui/ConsoleOutput.hpp"

#include <iostream>

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
    std::cout << "3. Back" << std::endl;
}

void ConsoleOutput::showInvalidChoice() const {
    std::cout << "Invalid choice" << std::endl;
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

void ConsoleOutput::showDealerStartHand() const {
    std::cout << "Dealer starting hand:" << std::endl;
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
    std::cout << "Do you want to take another card (yes or no)?" << std::endl;
}

void ConsoleOutput::showPlayerBust(const std::string& playerName) const {
    std::cout << playerName << " ... You are over 21..." << std::endl;
}

void ConsoleOutput::showRoundResult(const game::RoundResult resultCode, const std::string& playerName,
    const int playerValue, const int dealerValue) const {
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
    std::cout << "9. Blackjack is an Ace plus a 10-value card in the first two cards."
              << std::endl;

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
