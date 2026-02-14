#include "ui/ConsoleInput.hpp"

#include <iostream>
#include <limits>

int ConsoleInput::readInt() {
  int value = 0;
  std::cin >> value;
  return value;
}

std::string ConsoleInput::readWord() {
  std::string value;
  std::cin >> value;
  return value;
}

std::string ConsoleInput::readLine() {
  std::string value;
  std::getline(std::cin, value);
  return value;
}

void ConsoleInput::discardLine() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
