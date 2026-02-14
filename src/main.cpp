// Created by Kilian
#include <windows.h>

#include <iostream>
#include "game/BlackjackGame.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    game::BlackjackGame game;
    game.run();

    std::cerr << "Auf Wiedersehen :)!\n";
    return 0;
}
