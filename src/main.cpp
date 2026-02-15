// Created by Kilian
#include <windows.h>

#include "game/BlackjackGame.hpp"
#include <iostream>

int main() {
    // Aktiviert UTF-8-Ausgabe für Kartensymbole und Sonderzeichen in der Windows-Konsole.
    SetConsoleOutputCP(CP_UTF8);

    game::BlackjackGame game;
    game.run();

    std::cout << "Danke :)!\n";
    return 0;
}
