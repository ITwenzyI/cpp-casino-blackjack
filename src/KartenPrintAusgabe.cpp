//
// Created by Kilian on 13.05.25.
//

#include "KartenPrintAusgabe.h"
#include <iostream>

/*
KartenPrintAusgabe printer;

  std::vector<std::pair<std::string, std::string>> hand = {
    {"A", "♠"},
    {"10", "♥"},
    {"K", "♦"},
    {"7", "♣"}
  };

  printer.printCards(hand); nur karten
  printer.printCards(hand, 2); fügt am Ende 2 Verdeckte Karten hinzu.
*/

// Einzelkarte offen
std::vector<std::string> KartenPrintAusgabe::getCardLines(const std::string& rank, const std::string& suit) const {
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

// Einzelkarte verdeckt
std::vector<std::string> KartenPrintAusgabe::getVerdeckteKarte() const {
  return {
    "┌─────────┐",
    "│░░░░░░░░░│",
    "│░░░░░░░░░│",
    "│░░░░░░░░░│",
    "│░░░░░░░░░│",
    "│░░░░░░░░░│",
    "└─────────┘"
};
}

// Neue Version von printCards mit verdeckten Karten
void KartenPrintAusgabe::printCards(const std::vector<std::pair<std::string, std::string>>& cards, int verdeckteAnzahl) const {
  std::vector<std::vector<std::string>> allCardLines;

  // Offene Karten
  for (const auto& [rank, suit] : cards) {
    allCardLines.push_back(getCardLines(rank, suit));
  }

  // Verdeckte Karten
  for (int i = 0; i < verdeckteAnzahl; ++i) {
    allCardLines.push_back(getVerdeckteKarte());
  }

  // Zeilenweise drucken
  for (int i = 0; i < 7; ++i) {
    for (const auto& card : allCardLines) {
      std::cout << card[i] << " ";
    }
    std::cout << "\n";
  }
}


// Verdeckte Karten ausgeben
void KartenPrintAusgabe::printVerdeckteKarten(int anzahl) const {
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
