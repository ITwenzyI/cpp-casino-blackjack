#include "game/BlackjackRound.hpp"

namespace game {

void BlackjackRound::start() {
    playerStands_ = false;
    playerHand_.clear();
    dealerHand_.clear();
    deck_.reset();
    deck_.shuffle();

    dealerHand_.addCard(deck_.draw());
    playerHand_.addCard(deck_.draw());
    playerHand_.addCard(deck_.draw());
}

domain::Card BlackjackRound::playerHit() {
    const domain::Card card = deck_.draw();
    playerHand_.addCard(card);
    return card;
}

void BlackjackRound::playerStand() {
    playerStands_ = true;
}

std::vector<domain::Card> BlackjackRound::playDealerTurn() {
    std::vector<domain::Card> drawnCards;
    while (dealerHand_.value() < 17) {
        const domain::Card card = deck_.draw();
        dealerHand_.addCard(card);
        drawnCards.push_back(card);
    }
    return drawnCards;
}

const domain::Hand& BlackjackRound::playerHand() const {
    return playerHand_;
}

const domain::Hand& BlackjackRound::dealerHand() const {
    return dealerHand_;
}

int BlackjackRound::playerValue() const {
    return playerHand_.value();
}

int BlackjackRound::dealerValue() const {
    return dealerHand_.value();
}

bool BlackjackRound::playerHasBlackjack() const {
    return playerHand_.isBlackjack();
}

int BlackjackRound::evaluateResult() const {
    const int value_player = playerValue();
    const int value_dealer = dealerValue();

    if (value_dealer < 0 || value_player < 0) {
        return 0;
    }
    if (value_dealer > 21 && value_player <= 21) {
        return 2;
    }
    if (value_player > 21 && value_dealer <= 21) {
        return 1;
    }
    if (value_player > 21 && value_dealer > 21) {
        return 3;
    }
    if (value_player == value_dealer) {
        return 4;
    }
    if (value_player > value_dealer) {
        return 2;
    }
    return 1;
}

} // namespace game
