#ifndef UI_CONSOLE_INPUT_HPP
#define UI_CONSOLE_INPUT_HPP

#include <string>

class ConsoleInput {
 public:
  int readInt();
  std::string readWord();
  std::string readLine();
  void discardLine();
};

#endif
