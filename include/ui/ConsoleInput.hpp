#ifndef UI_CONSOLE_INPUT_HPP
#define UI_CONSOLE_INPUT_HPP

#include <string>

class ConsoleInput {
  public:
    // Liest eine ganze Zahl (z.B. Menüauswahl).
    int readInt();
    // Liest ein einzelnes Wort bis zum nächsten Whitespace.
    std::string readWord();
    // Liest eine komplette Zeile inklusive Leerzeichen.
    std::string readLine();
    // Verwirft den Rest der aktuellen Zeile im Eingabepuffer.
    void discardLine();
};

#endif
