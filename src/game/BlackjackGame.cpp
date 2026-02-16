//
// Created by Kilian on 13.05.25
// Updated by Kilian on 15.02.26
//
#include "game/BlackjackGame.hpp"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <thread>

#include "ui/ConsoleRenderer.hpp"
#include "util/BigText.hpp"

namespace {
// Helper mapping from domain object to renderer representation.
std::pair<std::string, std::string> toPrintableCard(const domain::Card& card) {
    return {card.rankText(), card.suitText()};
}
} // namespace

namespace game {

void BlackjackGame::run() {
    int choiceMainMenu = 0;
    int choiceSpielauswahl = 0;

    do {
        // Top-level casino menu.
        printBigText("Casino Menue");
        output_.showCasinoMenu();
        choiceMainMenu = input_.readInt();
        input_.discardLine();

        if (choiceMainMenu == 1) {
            output_.showGameSelectionMenu();
            choiceSpielauswahl = input_.readInt();
            input_.discardLine();

            if (choiceSpielauswahl == 1) {
                showBlackjackMenu();
            }
        }
    } while (choiceMainMenu == 1);
}

void BlackjackGame::showBlackjackMenu() {
    int choice;
    printBigText("BlackJack");
    output_.showBlackjackMenu();
    choice = input_.readInt();

    switch (choice) {
        case 1:
            playRound();
            break;
        case 2:
            showRules();
            break;
        case 3:
            return;
        default:
            output_.showInvalidChoice();
            break;
    }
}

void BlackjackGame::playRound() {
    ConsoleRenderer renderer;
    BlackjackRound round;
    int dealerHandValue = 0;
    int playerHandValue = 0;
    std::string playerName;

    // Remove a possible leftover newline after previous int input.
    input_.discardLine();
    playerName = input_.readLine();

    output_.showWelcome(playerName);
    output_.showGameStarting();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Start a new round including initial dealing from the game layer.
    round.start();
    clearRenderedHands();

    output_.showDealerStartHand();
    renderer.printHiddenCards(1);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    output_.showDealerVisualHand();
    // In this variant the dealer starts with one visible card.
    const domain::Card dealerStartCard = round.dealerHand().cards().front();
    dealerHandValue = round.dealerValue();
    buildHandDealer(dealerStartCard);
    output_.showDealerHandValue(dealerHandValue);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    output_.showSeparator();

    output_.showPlayerVisualHand(playerName);
    for (const domain::Card& playerCard : round.playerHand().cards()) {
        buildHandPlayer(playerCard);
    }
    playerHandValue = round.playerValue();

    output_.showPlayerHandValue(playerName, playerHandValue);

    if (round.playerHasBlackjack()) {
        output_.showPlayerBlackjack(playerName);
        output_.showBlackjackPayout(playerName);
        return;
    }

    output_.showDealerHandValue(dealerHandValue);

    bool weiter = true;
    // Player phase: draw cards until "no" or bust.
    while (weiter && playerHandValue < 21) {
        weiter = nextCardPlayer(round, playerName, playerHandValue);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    const std::vector<domain::Card> dealerCards = round.playDealerTurn();
    // Dealer phase including intermediate output for each drawn card.
    for (const domain::Card& dealerNewCard : dealerCards) {
        output_.showSeparator();
        output_.showDealerVisualHand();
        buildHandDealer(dealerNewCard);
        dealerHandValue = round.dealerValue();
        output_.showDealerHandValue(dealerHandValue);
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    dealerHandValue = round.dealerValue();
    if (dealerHandValue >= 17) {
        output_.showNoMoreDealerCards();
    }

    output_.showRoundResult(round.evaluateResult(), playerName, playerHandValue, dealerHandValue);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    output_.showSatisfactionPrompt();
    input_.readWord();
    clearRenderedHands();
}

bool BlackjackGame::nextCardPlayer(
    BlackjackRound& round, const std::string& playerName, int& playerHandValue) {
    std::string playerChoiceNextCard;

    output_.showHitPrompt();
    playerChoiceNextCard = input_.readWord();
    output_.showSeparator();

    std::transform(playerChoiceNextCard.begin(), playerChoiceNextCard.end(),
        playerChoiceNextCard.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    if (playerChoiceNextCard != "ja") {
        return false;
    }

    const domain::Card playerNewCard = round.playerHit();
    playerHandValue = round.playerValue();
    const int dealerHandValue = round.dealerValue();

    output_.showPlayerHandValue(playerName, playerHandValue);
    output_.showDealerHandValue(dealerHandValue);
    output_.showPlayerVisualHand(playerName);
    buildHandPlayer(playerNewCard);

    if (playerHandValue > 21) {
        output_.showPlayerBust(playerName);
    }

    return true;
}

void BlackjackGame::showRules() {
    printBigText("Regeln BJ");
    output_.showRules();
    input_.readInt();
}

void BlackjackGame::buildHandPlayer(const domain::Card& card) {
    // UI buffers cards so each new card can re-render the full hand.
    playerRenderedHand_.push_back(toPrintableCard(card));
    ConsoleRenderer renderer;
    renderer.printCards(playerRenderedHand_);
}

void BlackjackGame::buildHandDealer(const domain::Card& card) {
    dealerRenderedHand_.push_back(toPrintableCard(card));
    ConsoleRenderer renderer;
    renderer.printCards(dealerRenderedHand_);
}

void BlackjackGame::clearRenderedHands() {
    playerRenderedHand_.clear();
    dealerRenderedHand_.clear();
}

} // namespace game
