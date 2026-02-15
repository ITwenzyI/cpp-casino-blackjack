//
// Created by Kilian on 13.05.25.
//

#ifndef CONSOLE_RENDERER_HPP
#define CONSOLE_RENDERER_HPP
#include <string>
#include <vector>

class ConsoleRenderer {
  public:
    // Rendert offene Karten und optional zusätzliche verdeckte Karten rechts daneben.
    void printCards(const std::vector<std::pair<std::string, std::string>>& cards,
        int verdeckteAnzahl = 0) const;
    // Rendert nur verdeckte Karten.
    void printVerdeckteKarten(int anzahl) const;

  private:
    // Baut die 7 Textzeilen einer offenen Karte.
    std::vector<std::string> getCardLines(const std::string& rank, const std::string& suit) const;
    // Baut die 7 Textzeilen einer verdeckten Karte.
    std::vector<std::string> getVerdeckteKarte() const;
};

#endif //CONSOLE_RENDERER_HPP
