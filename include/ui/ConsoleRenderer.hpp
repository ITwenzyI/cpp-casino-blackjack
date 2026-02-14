//
// Created by Kilian on 13.05.25.
//

#ifndef CONSOLE_RENDERER_HPP
#define CONSOLE_RENDERER_HPP
#include <string>
#include <vector>

class ConsoleRenderer {
  public:
    void printCards(const std::vector<std::pair<std::string, std::string>>& cards,
        int verdeckteAnzahl = 0) const;
    void printVerdeckteKarten(int anzahl) const;

  private:
    std::vector<std::string> getCardLines(const std::string& rank, const std::string& suit) const;
    std::vector<std::string> getVerdeckteKarte() const;
};

#endif //CONSOLE_RENDERER_HPP
