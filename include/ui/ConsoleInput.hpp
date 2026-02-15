#ifndef UI_CONSOLE_INPUT_HPP
#define UI_CONSOLE_INPUT_HPP

#include <string>

class ConsoleInput {
  public:
    // Reads an integer (e.g. menu selection).
    int readInt();
    // Reads a single word until the next whitespace.
    std::string readWord();
    // Reads a full line including spaces.
    std::string readLine();
    // Discards the rest of the current line from the input buffer.
    void discardLine();
};

#endif
