//
// Created by Kilian on 13.05.25
// Updated by Kilian on 15.02.26
//
#include "game/BlackjackGame.hpp"

#include <algorithm>
#include <cctype>

#include "ui/ConsoleRenderer.hpp"
#include "util/BigText.hpp"

namespace {
// Helper mapping from domain object to renderer representation.
std::pair<std::string, std::string> toPrintableCard(const domain::Card& card) {
    return {card.rankText(), card.suitText()};
}

std::string toCardToken(const domain::Card& card) {
    return card.rankText() + card.suitText();
}

std::vector<std::string> toCardTokens(const domain::Hand& hand) {
    std::vector<std::string> tokens;
    tokens.reserve(hand.cards().size());
    for (const domain::Card& card : hand.cards()) {
        tokens.push_back(toCardToken(card));
    }
    return tokens;
}

int visibleDealerValue(const game::BlackjackRound& round) {
    const std::vector<domain::Card>& dealerCards = round.dealerHand().cards();
    domain::Hand visibleHand;

    for (std::size_t i = 0; i < dealerCards.size(); ++i) {
        // Keep the initially hidden first dealer card out of the visible HUD value.
        if (i == 0) {
            continue;
        }
        visibleHand.addCard(dealerCards[i]);
    }

    return visibleHand.value();
}
} // namespace

namespace game {

int BlackjackGame::readMenuChoice(const int minChoice, const int maxChoice) {
    while (true) {
        const int choice = input_.readInt();
        if (choice >= minChoice && choice <= maxChoice) {
            return choice;
        }
        output_.showInvalidChoice();
    }
}

void BlackjackGame::run() {
    int mainMenuChoice = 0;
    int gameSelectionChoice = 0;

    do {
        // Top-level casino menu.
        printBigText("Casino Menu");
        output_.showCasinoMenu();
        mainMenuChoice = readMenuChoice(0, 1);
        input_.discardLine();

        if (mainMenuChoice == 1) {
            output_.showGameSelectionMenu();
            gameSelectionChoice = readMenuChoice(1, 1);
            input_.discardLine();

            if (gameSelectionChoice == 1) {
                showBlackjackMenu();
            }
        }
    } while (mainMenuChoice == 1);
}

void BlackjackGame::showBlackjackMenu() {
    bool isInBlackjackMenu = true;
    while (isInBlackjackMenu) {
        int choice;
        printBigText("BlackJack");
        output_.showBlackjackMenu();
        choice = readMenuChoice(1, 4);

        switch (choice) {
            case 1:
                playRound();
                break;
            case 2:
                showRules();
                break;
            case 3:
                configurePacing();
                break;
            case 4:
                isInBlackjackMenu = false;
                break;
            default:
                output_.showInvalidChoice();
                break;
        }
    }
}

void BlackjackGame::configurePacing() {
    bool isConfiguring = true;
    while (isConfiguring) {
        output_.showPacingMenu(pacer_.mode());
        const int choice = readMenuChoice(1, 4);

        switch (choice) {
            case 1:
                pacer_.setMode(ui::PaceMode::Instant);
                output_.showPacingUpdated(pacer_.mode());
                break;
            case 2:
                pacer_.setMode(ui::PaceMode::Smooth);
                output_.showPacingUpdated(pacer_.mode());
                break;
            case 3:
                pacer_.setMode(ui::PaceMode::Cinematic);
                output_.showPacingUpdated(pacer_.mode());
                break;
            case 4:
                isConfiguring = false;
                break;
        }
    }
}

void BlackjackGame::playRound() {
    ConsoleRenderer renderer;
    std::string playerName;

    output_.promptUsername();
    // Remove a possible leftover newline after previous int input.
    input_.discardLine();
    playerName = input_.readLine();

    bool keepPlaying = true;
    while (keepPlaying) {
        BlackjackRound round;
        int dealerHandValue = 0;
        int playerHandValue = 0;

        output_.clearScreen();
        output_.showSection("Round Start");
        output_.showWelcome(playerName);
        output_.showGameStarting();
        pacer_.pauseMedium();

        // Start a new round including initial dealing from the game layer.
        round.start();
        clearRenderedHands();

        output_.showDealerStartHand();
        output_.showDrawingCard();
        pacer_.pauseMedium();
        renderer.printHiddenCards(1);
        pacer_.pauseMedium();

        output_.showDealerVisualHand();
        // Dealer shows only the second card while the first one stays hidden.
        const domain::Card dealerStartCard = round.dealerHand().cards().at(1);
        output_.showDealerDrawsCard();
        output_.showDrawingCard();
        pacer_.pauseMedium();
        dealerHandValue = visibleDealerValue(round);
        buildHandDealer(dealerStartCard);
        pacer_.pauseMedium();

        pacer_.pauseLong();
        output_.showSeparator();

        output_.showPlayerVisualHand(playerName);
        for (const domain::Card& playerCard : round.playerHand().cards()) {
            output_.showPlayerDrawsCard(playerName);
            output_.showDrawingCard();
            pacer_.pauseMedium();
            buildHandPlayer(playerCard);
            pacer_.pauseMedium();
        }
        playerHandValue = round.playerValue();

        output_.showRoundHud(playerName, playerHandValue, dealerHandValue, pacer_.mode());

        if (round.playerHasBlackjack()) {
            output_.clearScreen();
            output_.showSection("Result");
            renderDealerHand(true);
            renderPlayerHand(playerName);
            output_.showRoundHud(playerName, playerHandValue, dealerHandValue, pacer_.mode());
            output_.showPlayerBlackjack(playerName);
            pacer_.pauseShort();
            output_.showBlackjackPayout(playerName);
            pacer_.pauseMedium();
            output_.showContinuePrompt();
            input_.readLine();
            output_.showRoundSummary(playerName, toCardTokens(round.playerHand()), round.playerValue(),
                toCardTokens(round.dealerHand()), round.dealerValue(), game::RoundResult::PlayerWins);
            pacer_.pauseLong();
        } else {
            output_.clearScreen();
            output_.showSection("Player Turn");
            renderDealerHand(true);
            renderPlayerHand(playerName);
            output_.showRoundHud(playerName, playerHandValue, dealerHandValue, pacer_.mode());

            bool continueRound = true;
            // Player phase: draw cards until "no" or bust.
            while (continueRound && playerHandValue < 21) {
                output_.showRoundHud(playerName, playerHandValue, dealerHandValue, pacer_.mode());
                continueRound = nextCardPlayer(round, playerName, playerHandValue);
            }

            pacer_.pauseMedium();
            output_.clearScreen();
            output_.showSection("Dealer Turn");
            const domain::Card dealerHiddenCard = round.dealerHand().cards().front();
            output_.showDealerDrawsCard();
            output_.showDrawingCard();
            pacer_.pauseMedium();
            dealerRenderedHand_.insert(dealerRenderedHand_.begin(), toPrintableCard(dealerHiddenCard));
            dealerHandValue = round.dealerValue();
            renderDealerHand(false);
            renderPlayerHand(playerName);
            output_.showRoundHud(playerName, playerHandValue, dealerHandValue, pacer_.mode());
            pacer_.pauseMedium();

            const std::vector<domain::Card> dealerCards = round.playDealerTurn();
            // Dealer phase including intermediate output for each drawn card.
            for (const domain::Card& dealerNewCard : dealerCards) {
                output_.showDealerDrawsCard();
                output_.showDrawingCard();
                pacer_.pauseMedium();
                output_.showSeparator();
                output_.showDealerVisualHand();
                buildHandDealer(dealerNewCard);
                dealerHandValue = round.dealerValue();
                output_.showRoundHud(playerName, playerHandValue, dealerHandValue, pacer_.mode());
                pacer_.pauseMedium();
            }
            dealerHandValue = round.dealerValue();
            if (dealerHandValue >= 17) {
                output_.showNoMoreDealerCards();
                pacer_.pauseLong();
            }
            output_.showRoundHud(playerName, playerHandValue, dealerHandValue, pacer_.mode());
            pacer_.pauseLong();

            const game::RoundResult roundResult = round.evaluateResult();
            dealerHandValue = round.dealerValue();
            output_.showContinuePrompt();
            input_.readLine();
            output_.clearScreen();
            output_.showSection("Result");
            renderDealerHand(false);
            renderPlayerHand(playerName);
            output_.showRoundHud(playerName, playerHandValue, dealerHandValue, pacer_.mode());
            output_.showRoundResult(roundResult, playerName, playerHandValue, dealerHandValue);
            pacer_.pauseLong();
            output_.showRoundSummary(playerName, toCardTokens(round.playerHand()), round.playerValue(),
                toCardTokens(round.dealerHand()), round.dealerValue(), roundResult);
            pacer_.pauseLong();
        }

        pacer_.pauseShort();
        output_.showReplayMenu();
        const int replayChoice = readMenuChoice(1, 2);
        if (replayChoice == 1) {
            clearRenderedHands();
            continue;
        }
        if (replayChoice == 2) {
            keepPlaying = false;
            clearRenderedHands();
            continue;
        }
    }
}

bool BlackjackGame::nextCardPlayer(
    BlackjackRound& round, const std::string& playerName, int& playerHandValue) {
    std::string playerChoiceNextCard;

    while (true) {
        output_.showHitPrompt();
        playerChoiceNextCard = input_.readWord();
        input_.discardLine();
        output_.showSeparator();

        std::transform(playerChoiceNextCard.begin(), playerChoiceNextCard.end(),
            playerChoiceNextCard.begin(),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

        if (playerChoiceNextCard == "yes" || playerChoiceNextCard == "ja" ||
            playerChoiceNextCard == "h" || playerChoiceNextCard == "hit") {
            break;
        }
        if (playerChoiceNextCard == "no" || playerChoiceNextCard == "nein" ||
            playerChoiceNextCard == "s" || playerChoiceNextCard == "stand") {
            return false;
        }
        output_.showInvalidYesNo();
    }

    const domain::Card playerNewCard = round.playerHit();
    playerHandValue = round.playerValue();
    const int dealerHandValue = visibleDealerValue(round);

    output_.showPlayerDrawsCard(playerName);
    output_.showDrawingCard();
    pacer_.pauseShort();
    output_.showRoundHud(playerName, playerHandValue, dealerHandValue, pacer_.mode());
    output_.showPlayerVisualHand(playerName);
    buildHandPlayer(playerNewCard);
    pacer_.pauseShort();

    if (playerHandValue > 21) {
        output_.showPlayerBust(playerName);
    }

    return true;
}

void BlackjackGame::showRules() {
    printBigText("Rules BJ");
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

void BlackjackGame::renderPlayerHand(const std::string& playerName) const {
    output_.showPlayerVisualHand(playerName);
    ConsoleRenderer renderer;
    renderer.printCards(playerRenderedHand_);
}

void BlackjackGame::renderDealerHand(const bool withHiddenCard) const {
    output_.showDealerVisualHand();
    ConsoleRenderer renderer;
    if (withHiddenCard) {
        renderer.printHiddenCards(1);
    }
    renderer.printCards(dealerRenderedHand_);
}

} // namespace game
