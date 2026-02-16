#include "game/BlackjackRound.hpp"

namespace game {

void BlackjackRound::start() {
    playerStands_ = false;
    playerHand_.clear();
    dealerHand_.clear();
    deck_.reset();
    deck_.shuffle();

    // Current game variant: dealer starts with 1 visible card, player with 2.
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
    // Standard dealer rule.
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

RoundResult BlackjackRound::evaluateResult() const {
    const int value_player = playerValue();
    const int value_dealer = dealerValue();

    // Typed result values are used by the game orchestrator for UI output.
    if (value_dealer < 0 || value_player < 0) {
        return RoundResult::Invalid;
    }
    if (value_dealer > 21 && value_player <= 21) {
        return RoundResult::PlayerWins;
    }
    if (value_player > 21 && value_dealer <= 21) {
        return RoundResult::DealerWins;
    }
    if (value_player > 21 && value_dealer > 21) {
        return RoundResult::BothBust;
    }
    if (value_player == value_dealer) {
        return RoundResult::Push;
    }
    if (value_player > value_dealer) {
        return RoundResult::PlayerWins;
    }
    return RoundResult::DealerWins;
}

} // namespace game
