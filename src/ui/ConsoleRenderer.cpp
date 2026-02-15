//
// Created by Kilian on 13.05.25.
//

#include "ui/ConsoleRenderer.hpp"
#include <iostream>

// Renderer arbeitet zeilenbasiert: jede Karte wird als 7 Textzeilen aufgebaut.
std::vector<std::string> ConsoleRenderer::getCardLines(
    const std::string& rank, const std::string& suit) const {
    std::vector<std::string> card(7);
    card[0] = "┌─────────┐";
    card[1] = "│ " + rank + (rank.size() == 1 ? "       " : "      ") + "│";
    card[2] = "│         │";
    card[3] = "│    " + suit + "    │";
    card[4] = "│         │";
    card[5] = "│       " + (rank.size() == 1 ? rank + " " : rank) + "│";
    card[6] = "└─────────┘";
    return card;
}

// Rückseiten-Darstellung für verdeckte Dealer-Karten.
std::vector<std::string> ConsoleRenderer::getVerdeckteKarte() const {
    return {"┌─────────┐", "│░░░░░░░░░│", "│░░░░░░░░░│", "│░░░░░░░░░│", "│░░░░░░░░░│",
        "│░░░░░░░░░│", "└─────────┘"};
}

void ConsoleRenderer::printCards(
    const std::vector<std::pair<std::string, std::string>>& cards, int verdeckteAnzahl) const {
    std::vector<std::vector<std::string>> allCardLines;

    for (const auto& [rank, suit] : cards) {
        allCardLines.push_back(getCardLines(rank, suit));
    }

    for (int i = 0; i < verdeckteAnzahl; ++i) {
        allCardLines.push_back(getVerdeckteKarte());
    }

    // Gleiche Zeile aller Karten zusammen ausgeben => horizontale Handdarstellung.
    for (int i = 0; i < 7; ++i) {
        for (const auto& card : allCardLines) {
            std::cout << card[i] << " ";
        }
        std::cout << "\n";
    }
}

void ConsoleRenderer::printVerdeckteKarten(int anzahl) const {
    std::vector<std::vector<std::string>> allCards;
    for (int i = 0; i < anzahl; ++i) {
        allCards.push_back(getVerdeckteKarte());
    }

    for (int zeile = 0; zeile < 7; ++zeile) {
        for (const auto& karte : allCards) {
            std::cout << karte[zeile] << " ";
        }
        std::cout << "\n";
    }
}
