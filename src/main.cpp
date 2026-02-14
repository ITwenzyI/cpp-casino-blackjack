// Created by Kilian
#include <windows.h>

#include "game/BlackjackGame.hpp"
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    game::BlackjackGame game;
    game.run();

    std::cerr << "Auf Wiedersehen :)!\n";
    return 0;
}
