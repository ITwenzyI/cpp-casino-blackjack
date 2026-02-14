//
// Created by Kilian on 13.05.25.
//
#include "game/BlackjackGame.hpp"

#include <algorithm>
#include <chrono>
#include <cctype>
#include <iostream>
#include <thread>

#include "ui/ConsoleRenderer.hpp"
#include "util/BigText.hpp"

namespace {
std::pair<std::string, std::string> toPrintableCard(const domain::Card& card) {
  return {card.rankText(), card.suitText()};
}
} // namespace

namespace game {

void BlackjackGame::run() {
  int choiceMainMenu = 0;
  int choiceSpielauswahl = 0;

  do {
    printBigText("Casino Menu");
    std::cout << "|====| Deluxe Casino |====|" << std::endl;
    std::cout << "1. Spielauswahl" << std::endl;
    std::cout << "Deine Auswahl: " << std::endl;
    choiceMainMenu = input_.readInt();
    input_.discardLine();

    if (choiceMainMenu == 1) {
      std::cout << "|====| Spielauswahl |====|" << std::endl;
      std::cout << "-|- Karten Spiele -|-" << std::endl;
      std::cout << "1. Blackjack" << std::endl;
      std::cout << "Deine Auswahl: " << std::endl;
      choiceSpielauswahl = input_.readInt();
      input_.discardLine();

      if (choiceSpielauswahl == 1) {
        showBlackjackMenu();
      }
    }
  } while (choiceMainMenu == 1);
}

void BlackjackGame::showBlackjackMenu() {
  int choice;
  printBigText("BlackJack");
  std::cout << "|====| Main Menue|====|" << std::endl;
  std::cout << "1. Spiel starten" << std::endl;
  std::cout << "2. Regeln" << std::endl;
  std::cout << "3. Zurueck" << std::endl;
  choice = input_.readInt();

  switch (choice) {
    case 1: playRound(); break;
    case 2: showRules(); break;
    case 3: return;
    default: std::cout << "Invalid choice" << std::endl; break;
  }
}

void BlackjackGame::playRound() {
  ConsoleRenderer renderer;
  BlackjackRound round;
  int dealerHandValue = 0;
  int playerHandValue = 0;
  std::string playerName;

  std::cout << "Gebe deinen Benutzernamen ein:" << std::endl;
  input_.discardLine();
  playerName = input_.readLine();

  std::cout << "Willkommen in Blackjack " << playerName << std::endl;
  std::cout << "Das Spiel startet..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));

  round.start();
  clearRenderedHands();

  std::cout << "Dealers beginn Hand:" << std::endl;
  renderer.printVerdeckteKarten(1);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::cout << "Dealers aktuelle optische Hand:" << std::endl;
  const domain::Card dealerStartCard = round.dealerHand().cards().front();
  dealerHandValue = round.dealerValue();
  buildHandDealer(dealerStartCard);
  std::cout << "Dealers aktueller Handwert: " << dealerHandValue << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "----------------------------------------------------------" << std::endl;

  std::cout << playerName << "s aktuelle optische Hand:" << std::endl;
  for (const domain::Card& playerCard : round.playerHand().cards()) {
    buildHandPlayer(playerCard);
  }
  playerHandValue = round.playerValue();

  std::cout << playerName << " aktueller Handwert: " << playerHandValue << std::endl;

  if (round.playerHasBlackjack()) {
    std::cout << playerName << " hat einen BLACKJACK!" << std::endl;
    std::cout << playerName << " gewinnt automatisch mit einem Blackjack und bekommt den 1.5-fachen Einsatz zurueck."
              << std::endl;
    return;
  }

  std::cout << "Dealers aktueller Handwert: " << dealerHandValue << std::endl;

  bool weiter = true;
  while (weiter && playerHandValue < 21) {
    weiter = nextCardPlayer(round, playerName, playerHandValue);
  }

  std::this_thread::sleep_for(std::chrono::seconds(2));

  const std::vector<domain::Card> dealerCards = round.playDealerTurn();
  for (const domain::Card& dealerNewCard : dealerCards) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "Dealers aktuelle optische Hand:" << std::endl;
    buildHandDealer(dealerNewCard);
    dealerHandValue = round.dealerValue();
    std::cout << "Dealers aktueller Handwert: " << dealerHandValue << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }
  dealerHandValue = round.dealerValue();
  if (dealerHandValue >= 17) {
    std::cout << "Keine Karte mehr fuer Dealer!" << std::endl;
  }

  switch (round.evaluateResult()) {
    case 1:
      std::cout << "\nDer Dealer hat gewonnen mit: " << dealerHandValue << " Punkten!" << std::endl;
      std::cout << playerName << " verliert seinen Einsatz leider." << std::endl;
      std::cout << "Beim naechsten mal wird es der Gewinn!" << std::endl;
      break;
    case 2:
      std::cout << "\n" << playerName << " hat gewonnen mit: " << playerHandValue << " Punkten!" << std::endl;
      std::cout << playerName << " bekommt seinen Einsatz 2x zurueck." << std::endl;
      std::cout << "Glueckwunsch zum Sieg!!!" << std::endl;
      break;
    case 3:
      std::cout << "\n" << playerName << " und der Dealer haben beide ueber 21 Punkte!" << std::endl;
      std::cout << "Somit gewinnt niemand und " << playerName << " verliert seinen Einsatz!" << std::endl;
      std::cout << "Beim naechsten mal wird es der Gewinn!" << std::endl;
      break;
    case 4:
      std::cout << "\nUnentschieden zwischen " << playerName << " und dem Dealer mit jeweils " << playerHandValue
                << " Punkten!" << std::endl;
      std::cout << playerName << " bekommt seinen Einsatz zurueck." << std::endl;
      std::cout << "Glueckwunsch zum Unentschieden!" << std::endl;
      break;
    default:
      std::cerr << "\nFehler!" << std::endl;
      break;
  }

  std::this_thread::sleep_for(std::chrono::seconds(3));

  std::string ende;
  std::cout << "\n\nBist du zufrieden?" << std::endl;
  ende = input_.readWord();
  clearRenderedHands();
}

bool BlackjackGame::nextCardPlayer(BlackjackRound& round, const std::string& playerName, int& playerHandValue) {
  std::string playerChoiceNextCard;

  std::cout << "Moechtest du noch eine Karte nehmen (Ja oder Nein)?" << std::endl;
  playerChoiceNextCard = input_.readWord();
  std::cout << "----------------------------------------------------------" << std::endl;

  std::transform(
      playerChoiceNextCard.begin(), playerChoiceNextCard.end(), playerChoiceNextCard.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
      });

  if (playerChoiceNextCard != "ja") {
    return false;
  }

  const domain::Card playerNewCard = round.playerHit();
  playerHandValue = round.playerValue();
  const int dealerHandValue = round.dealerValue();

  std::cout << playerName << "s aktueller Handwert: " << playerHandValue << std::endl;
  std::cout << "Dealers aktueller Handwert: " << dealerHandValue << std::endl;
  std::cout << playerName << "s aktuelle optische Hand:" << std::endl;
  buildHandPlayer(playerNewCard);

  if (playerHandValue > 21) {
    std::cout << playerName << " ... Du bist leider ueber 21..." << std::endl;
  }

  return true;
}

void BlackjackGame::showRules() {
  int uselessChoice = 0;
  printBigText("Regeln BJ");
  std::cout << "|====| Allgemeines Ziel |====|" << std::endl;
  std::cout << "1. Ziel des Spiels ist es, so nah wie moeglich an 21 Punkte zu kommen." << std::endl;
  std::cout << "2. Wer mehr als 21 Punkte hat, verliert automatisch (Bust)." << std::endl;

  std::cout << std::endl << "|====| Kartenwerte |====|" << std::endl;
  std::cout << "3. Zahlenkarten zaehlen entsprechend ihrem Zahlenwert (z. B. 2-10)." << std::endl;
  std::cout << "4. Bube, Dame und Koenig zaehlen jeweils 10 Punkte." << std::endl;
  std::cout << "5. Das Ass zaehlt 1 oder 11 Punkte - je nachdem, was guenstiger ist." << std::endl;

  std::cout << std::endl << "|====| Spielverlauf |====|" << std::endl;
  std::cout << "6. Jeder Spieler erhaelt zu Beginn zwei Karten." << std::endl;
  std::cout << "7. Der Spieler entscheidet, ob er eine weitere Karte zieht ('Hit') oder keine mehr ('Stand')." << std::endl;
  std::cout << "8. Das Ziel ist, naeher an 21 zu kommen als der Dealer, ohne sie zu ueberschreiten." << std::endl;
  std::cout << "9. Ein Blackjack besteht aus Ass + 10er-Karte mit den ersten beiden Karten." << std::endl;

  std::cout << std::endl << "|====| Dealer-Regeln |====|" << std::endl;
  std::cout << "10. Der Dealer spielt zuletzt." << std::endl;
  std::cout << "11. Der Dealer muss bei 16 oder weniger Punkten Karten ziehen." << std::endl;
  std::cout << "12. Der Dealer muss bei 17 oder mehr Punkten stoppen." << std::endl;

  std::cout << std::endl << "|====| Gewinn & Verlust |====|" << std::endl;
  std::cout << "13. Wer naeher an 21 ist als der Dealer, gewinnt." << std::endl;
  std::cout << "14. Bei Punktegleichstand bleibt der Einsatz erhalten." << std::endl;
  std::cout << "===============================" << std::endl;
  uselessChoice = input_.readInt();
}

void BlackjackGame::buildHandPlayer(const domain::Card& card) {
  playerRenderedHand_.push_back(toPrintableCard(card));
  ConsoleRenderer renderer;
  renderer.printCards(playerRenderedHand_);
}

void BlackjackGame::buildHandDealer(const domain::Card& card) {
  dealerRenderedHand_.push_back(toPrintableCard(card));
  ConsoleRenderer renderer;
  renderer.printCards(dealerRenderedHand_);
}

void BlackjackGame::clearRenderedHands() {
  playerRenderedHand_.clear();
  dealerRenderedHand_.clear();
}

} // namespace game


