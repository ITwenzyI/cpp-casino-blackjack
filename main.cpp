// Created by Kilian
#include <windows.h>
#include <io.h>
//Standard Includes:
#include "iostream"
#include <string>

//Header Includes:
#include "include/BlackJack.h"
#include "include/BigText.h"


using namespace std;
int main() {
    SetConsoleOutputCP(CP_UTF8);

    BlackJack blackjack;
    int choice_mainmenu;
    int choice_spielauswahl;


    do {
        printBigText("Casino Menu");
        cout << "|====| Deluxe Casino |====|" << endl;
        cout << "1. Spielauswahl" << endl;
        cout << "Deine Auswahl: " << endl;
        cin >> choice_mainmenu;
        cin.ignore();

        if (choice_mainmenu == 1) {
            cout << "|====| Spielauswahl |====|" << endl;
            cout << "-|- Karten Spiele -|-" << endl;
            cout << "1. Blackjack" << endl;
            cout << "Deine Auswahl: " << endl;
            cin >> choice_spielauswahl;
            cin.ignore();

            switch (choice_spielauswahl) {
                case 1: blackjack.mainmenu_bj(); break;
                default: break;
            }
        }

    } while (choice_mainmenu == 1);

    std::cerr << "Auf Wiedersehen :)!\n";
    return 0;
}
