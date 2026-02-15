// Created by Kilian
#include <windows.h>

#include "game/BlackjackGame.hpp"
#include <iostream>

int main() {
    // Enables UTF-8 output for card symbols and special characters in the Windows console.
    SetConsoleOutputCP(CP_UTF8);

    game::BlackjackGame game;
    game.run();

    std::cout << "Danke :)!\n";
    return 0;
}
