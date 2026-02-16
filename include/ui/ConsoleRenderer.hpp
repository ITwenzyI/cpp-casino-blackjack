//
// Created by Kilian on 13.05.25.
//

#ifndef CONSOLE_RENDERER_HPP
#define CONSOLE_RENDERER_HPP
#include <string>
#include <vector>

class ConsoleRenderer {
  public:
    // Renders open cards and optional additional hidden cards to the right.
    void printCards(const std::vector<std::pair<std::string, std::string>>& cards,
        int hiddenCount = 0) const;
    // Renders only hidden cards.
    void printHiddenCards(int count) const;

  private:
    // Builds the 7 text lines of an open card.
    std::vector<std::string> getCardLines(const std::string& rank, const std::string& suit) const;
    // Builds the 7 text lines of a hidden card.
    std::vector<std::string> getHiddenCardLines() const;
};

#endif //CONSOLE_RENDERER_HPP
