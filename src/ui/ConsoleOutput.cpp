#include "ui/ConsoleOutput.hpp"

#include <iostream>

void ConsoleOutput::showCasinoMenu() const {
    std::cout << "|====| Deluxe Casino |====|" << std::endl;
    std::cout << "1. Spielauswahl" << std::endl;
    std::cout << "0. Beenden" << std::endl;
    std::cout << "Deine Auswahl:" << std::endl;
}

void ConsoleOutput::showGameSelectionMenu() const {
    std::cout << "|====| Spielauswahl |====|" << std::endl;
    std::cout << "-|- Karten Spiele -|-" << std::endl;
    std::cout << "1. Blackjack" << std::endl;
    std::cout << "Deine Auswahl:" << std::endl;
}

void ConsoleOutput::showBlackjackMenu() const {
    std::cout << "|====| Main Menue|====|" << std::endl;
    std::cout << "1. Spiel starten" << std::endl;
    std::cout << "2. Regeln" << std::endl;
    std::cout << "3. Zurueck" << std::endl;
}

void ConsoleOutput::showInvalidChoice() const {
    std::cout << "Invalid choice" << std::endl;
}

void ConsoleOutput::showWelcome(const std::string& playerName) const {
    std::cout << "Willkommen in Blackjack " << playerName << std::endl;
}

void ConsoleOutput::showGameStarting() const {
    std::cout << "Das Spiel startet..." << std::endl;
}

void ConsoleOutput::showSeparator() const {
    std::cout << "----------------------------------------------------------" << std::endl;
}

void ConsoleOutput::showDealerStartHand() const {
    std::cout << "Dealers beginn Hand:" << std::endl;
}

void ConsoleOutput::showDealerVisualHand() const {
    std::cout << "Dealers aktuelle optische Hand:" << std::endl;
}

void ConsoleOutput::showDealerHandValue(const int handValue) const {
    std::cout << "Dealers aktueller Handwert: " << handValue << std::endl;
}

void ConsoleOutput::showNoMoreDealerCards() const {
    std::cout << "Keine Karte mehr fuer Dealer!" << std::endl;
}

void ConsoleOutput::showPlayerVisualHand(const std::string& playerName) const {
    std::cout << playerName << "s aktuelle optische Hand:" << std::endl;
}

void ConsoleOutput::showPlayerHandValue(const std::string& playerName, const int handValue) const {
    std::cout << playerName << " aktueller Handwert: " << handValue << std::endl;
}

void ConsoleOutput::showPlayerBlackjack(const std::string& playerName) const {
    std::cout << playerName << " hat einen BLACKJACK!" << std::endl;
}

void ConsoleOutput::showBlackjackPayout(const std::string& playerName) const {
    std::cout
        << playerName
        << " gewinnt automatisch mit einem Blackjack und bekommt den 1.5-fachen Einsatz zurueck."
        << std::endl;
}

void ConsoleOutput::showHitPrompt() const {
    std::cout << "Moechtest du noch eine Karte nehmen (Ja oder Nein)?" << std::endl;
}

void ConsoleOutput::showPlayerBust(const std::string& playerName) const {
    std::cout << playerName << " ... Du bist leider ueber 21..." << std::endl;
}

void ConsoleOutput::showRoundResult(const int resultCode, const std::string& playerName,
    const int playerValue, const int dealerValue) const {
    std::cout << std::endl;
    switch (resultCode) {
        case 1:
            std::cout << "Der Dealer hat gewonnen mit: " << dealerValue << " Punkten!" << std::endl;
            std::cout << playerName << " verliert seinen Einsatz leider." << std::endl;
            std::cout << "Beim naechsten mal wird es der Gewinn!" << std::endl;
            break;
        case 2:
            std::cout << playerName << " hat gewonnen mit: " << playerValue << " Punkten!"
                      << std::endl;
            std::cout << playerName << " bekommt seinen Einsatz 2x zurueck." << std::endl;
            std::cout << "Glueckwunsch zum Sieg!!!" << std::endl;
            break;
        case 3:
            std::cout << playerName << " und der Dealer haben beide ueber 21 Punkte!" << std::endl;
            std::cout << "Somit gewinnt niemand und " << playerName << " verliert seinen Einsatz!"
                      << std::endl;
            std::cout << "Beim naechsten mal wird es der Gewinn!" << std::endl;
            break;
        case 4:
            std::cout << "Unentschieden zwischen " << playerName << " und dem Dealer mit jeweils "
                      << playerValue << " Punkten!" << std::endl;
            std::cout << playerName << " bekommt seinen Einsatz zurueck." << std::endl;
            std::cout << "Glueckwunsch zum Unentschieden!" << std::endl;
            break;
        default:
            showError();
            break;
    }
}

void ConsoleOutput::showSatisfactionPrompt() const {
    std::cout << std::endl << std::endl;
    std::cout << "Vielen dank für das spielen von Kilians Blackjack!" << "\n Bist du zufrieden?"
              << std::endl;
}

void ConsoleOutput::showRules() const {
    std::cout << "|====| Allgemeines Ziel |====|" << std::endl;
    std::cout << "1. Ziel des Spiels ist es, so nah wie moeglich an 21 Punkte zu kommen."
              << std::endl;
    std::cout << "2. Wer mehr als 21 Punkte hat, verliert automatisch (Bust)." << std::endl;

    std::cout << std::endl << "|====| Kartenwerte |====|" << std::endl;
    std::cout << "3. Zahlenkarten zaehlen entsprechend ihrem Zahlenwert (z. B. 2-10)." << std::endl;
    std::cout << "4. Bube, Dame und Koenig zaehlen jeweils 10 Punkte." << std::endl;
    std::cout << "5. Das Ass zaehlt 1 oder 11 Punkte - je nachdem, was guenstiger ist."
              << std::endl;

    std::cout << std::endl << "|====| Spielverlauf |====|" << std::endl;
    std::cout << "6. Jeder Spieler erhaelt zu Beginn zwei Karten." << std::endl;
    std::cout << "7. Der Spieler entscheidet, ob er eine weitere Karte zieht ('Hit') oder keine "
                 "mehr ('Stand')."
              << std::endl;
    std::cout
        << "8. Das Ziel ist, naeher an 21 zu kommen als der Dealer, ohne sie zu ueberschreiten."
        << std::endl;
    std::cout << "9. Ein Blackjack besteht aus Ass + 10er-Karte mit den ersten beiden Karten."
              << std::endl;

    std::cout << std::endl << "|====| Dealer-Regeln |====|" << std::endl;
    std::cout << "10. Der Dealer spielt zuletzt." << std::endl;
    std::cout << "11. Der Dealer muss bei 16 oder weniger Punkten Karten ziehen." << std::endl;
    std::cout << "12. Der Dealer muss bei 17 oder mehr Punkten stoppen." << std::endl;

    std::cout << std::endl << "|====| Gewinn & Verlust |====|" << std::endl;
    std::cout << "13. Wer naeher an 21 ist als der Dealer, gewinnt." << std::endl;
    std::cout << "14. Bei Punktegleichstand bleibt der Einsatz erhalten." << std::endl;
    std::cout << "===============================" << std::endl;
}

void ConsoleOutput::showError() const {
    std::cerr << "Fehler!" << std::endl;
}
