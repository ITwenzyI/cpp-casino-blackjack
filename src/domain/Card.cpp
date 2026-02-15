#include "domain/Card.hpp"

namespace domain {

Card::Card(const int rank, const Suit suit) : rank_(rank), suit_(suit) {
}

int Card::rank() const {
    return rank_;
}

Suit Card::suit() const {
    return suit_;
}

int Card::blackjackValue() const {
    // Ass wird hier als 11 gewertet; Hand::value() korrigiert später ggf. auf 1.
    if (rank_ == 14) {
        return 11;
    }
    if (rank_ > 10) {
        return 10;
    }
    return rank_;
}

std::string Card::rankText() const {
    switch (rank_) {
        case 11:
            return "K";
        case 12:
            return "D";
        case 13:
            return "J";
        case 14:
            return "A";
        default:
            return std::to_string(rank_);
    }
}

std::string Card::suitText() const {
    switch (suit_) {
        case Suit::Spades:
            return "♠";
        case Suit::Hearts:
            return "♥";
        case Suit::Diamonds:
            return "♦";
        case Suit::Clubs:
            return "♣";
        default:
            return "?";
    }
}

} // namespace domain
