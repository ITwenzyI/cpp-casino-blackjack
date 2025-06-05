// Created by Kilian
#include <windows.h>
#include <io.h>
#include <fcntl.h>
//Standard Includes:
#include "iostream"
#include <vector>
#include <string>

//Header Includes:
#include "include/BlackJack.h"
#include "include/KartenPrintAusgabe.h"
#include "include/BigText.h"


using namespace std;
int main() {
    SetConsoleOutputCP(CP_UTF8);

    BlackJack blackjack;
    int choice_mainmenu;
    int choice_spielauswahl;
    int choice_account;
    int choice_achievments;


    do {
        printBigText("Casino Menu");
        cout << "|====| Deluxe Casino |====|" << endl;
        cout << "1. Spielauswahl" << endl;
        cout << "2. Account verwalten" << endl;
        cout << "3. Achievment verwalten" << endl;
        cout << "Deine Auswahl: " << endl;
        cin >> choice_mainmenu;
        cin.ignore();

        if (choice_mainmenu == 1) {
            cout << "|====| Spielauswahl |====|" << endl;
            cout << "-|- Karten Spiele -|-" << endl;
            cout << "1. Blackjack" << endl;
            cout << ". Roulett" << endl;
            cout << ". Durak" << endl;
            cout << "-|- Exclusive Spiele -|-" << endl;
            cout << ". Zahlen erraten" << endl;
            cout << ". Glücksrad" << endl;
            cout << ". Slots" << endl;
            cout << "Deine Auswahl: " << endl;
            cin >> choice_spielauswahl;
            cin.ignore();

            switch (choice_spielauswahl) {
                case 1: blackjack.mainmenu_bj(); break;
                case 2: blackjack.startplay_bj(); break;
            }
        }

        if (choice_mainmenu == 2) {
            cout << "|====| Account verwalten |====|" << endl;
            cout << ". Account bearbeiten" << endl;
            cout << ". Stats anschauen" << endl;
            cout << ". Freunde verwalten" << endl;
            cout << "Deine Auswahl: " << endl;
            cin >> choice_account;
            cin.ignore();
        }

        if (choice_mainmenu == 3) {
            cout << "|====| Achievment verwalten |====|" << endl;
            cout << ". Achievments anschauen" << endl;
            cout << ". Fehlende Achievments anschauen" << endl;
            cout << "Deine Auswahl: " << endl;
            cin >> choice_achievments;
            cin.ignore();
        }
    } while (choice_mainmenu < 4 && choice_mainmenu > 0);

    std::cerr << "Auf Wiedersehen :)!\n";
    return 0;
}
