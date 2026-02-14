//
// Created by Kilian on 13.05.25.
//
#include <algorithm>
#include <chrono>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <vector>

#include "BlackJack.h"
#include "ui/ConsoleRenderer.hpp"
#include "util/BigText.hpp"

using namespace std;

namespace {
int usless_choice;
std::vector<std::pair<std::string, std::string>> g_playerRenderedHand;
std::vector<std::pair<std::string, std::string>> g_dealerRenderedHand;

std::pair<std::string, std::string> toPrintableCard(const domain::Card& card) {
  return {card.rankText(), card.suitText()};
}
}

void BlackJack::mainmenu_bj() {
  int choice;
  printBigText("BlackJack");
  std::cout << "|====| Main Menue|====|" << std::endl;
  cout << "1. Spiel starten" << endl;
  cout << "2. Regeln" << endl;
  cout << "3. Zurueck" << endl;
  cin >> choice;

  switch (choice) {
    case 1: startplay_bj(); break;
    case 2: rules_bj(); break;
    case 3: return;
    default: cout << "Invalid choice" << endl; break;
  }
}

void BlackJack::startplay_bj() {
  ConsoleRenderer renderer;
  domain::Deck deck;
  domain::Hand player_hand;
  domain::Hand dealer_hand;

  int dealer_hand_valueall = 0;
  int player_hand_valueall = 0;
  std::string player_name;

  cout << "Gebe deinen Benutzernamen ein:" << endl;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  getline(cin, player_name);

  cout << "Willkommen in Blackjack " << player_name << endl;

  cout << "Das Spiel startet..." << endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));

  deck.shuffle();
  clear_rendered_hands();

  cout << "Dealers beginn Hand:" << endl;
  renderer.printVerdeckteKarten(1);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  cout << "Dealers aktuelle optische Hand:" << endl;
  const domain::Card dealer_start_card = deck.draw();
  dealer_hand.addCard(dealer_start_card);
  dealer_hand_valueall = dealer_hand.value();

  build_hand_dealer(dealer_start_card);
  cout << "Dealers aktueller Handwert: " << dealer_hand_valueall << endl;

  std::this_thread::sleep_for(std::chrono::seconds(3));

  cout << "----------------------------------------------------------" << endl;

  cout << player_name << "s aktuelle optische Hand:" << endl;
  for (int i = 0; i < 2; ++i) {
    const domain::Card player_card = deck.draw();
    player_hand.addCard(player_card);
    build_hand_player(player_card);
  }
  player_hand_valueall = player_hand.value();

  cout << player_name << " aktueller Handwert: " << player_hand_valueall << endl;

  if (player_hand_valueall == 21) {
    cout << player_name << " hat einen BLACKJACK!" << endl;
    cout << player_name << " gewinnt automatisch mit einem Blackjack und bekommt den 1.5-fachen Einsatz zurueck." << endl;
    return;
  }

  cout << "Dealers aktueller Handwert: " << dealer_hand_valueall << endl;

  bool weiter = true;
  while (weiter && player_hand_valueall < 21) {
    weiter = nextcard_player(player_hand, deck, player_name, dealer_hand_valueall, player_hand_valueall);
  }

  std::this_thread::sleep_for(std::chrono::seconds(2));

  while (dealer_hand_valueall < 17) {
    cout << "----------------------------------------------------------" << endl;
    cout << "Dealers aktuelle optische Hand:" << endl;

    const domain::Card dealer_new_card = deck.draw();
    dealer_hand.addCard(dealer_new_card);
    dealer_hand_valueall = dealer_hand.value();

    build_hand_dealer(dealer_new_card);
    cout << "Dealers aktueller Handwert: " << dealer_hand_valueall << endl;

    if (dealer_hand_valueall >= 17) {
      cout << "Keine Karte mehr fuer Dealer!" << endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
  }

  switch (result_game(player_hand_valueall, dealer_hand_valueall)) {
    case 1:
      cout << "\nDer Dealer hat gewonnen mit: " << dealer_hand_valueall << " Punkten!" << endl;
      cout << player_name << " verliert seinen Einsatz leider." << endl;
      cout << "Beim naechsten mal wird es der Gewinn!" << endl;
      break;
    case 2:
      cout << "\n" << player_name << " hat gewonnen mit: " << player_hand_valueall << " Punkten!" << endl;
      cout << player_name << " bekommt seinen Einsatz 2x zurueck." << endl;
      cout << "Glueckwunsch zum Sieg!!!" << endl;
      break;
    case 3:
      cout << "\n" << player_name << " und der Dealer haben beide ueber 21 Punkte!" << endl;
      cout << "Somit gewinnt niemand und " << player_name << " verliert seinen Einsatz!" << endl;
      cout << "Beim naechsten mal wird es der Gewinn!" << endl;
      break;
    case 4:
      cout << "\n"
           << "Unentschieden zwischen " << player_name << " und dem Dealer mit jeweils " << player_hand_valueall << " Punkten!"
           << endl;
      cout << player_name << " bekommt seinen Einsatz zurueck." << endl;
      cout << "Glueckwunsch zum Unentschieden!" << endl;
      break;
    default:
      cerr << "\n"
           << "Fehler!" << endl;
      break;
  }

  std::this_thread::sleep_for(std::chrono::seconds(3));

  string ende;
  cout << "\n\nBist du zufrieden?" << endl;
  cin >> ende;
  clear_rendered_hands();
}

bool BlackJack::nextcard_player(domain::Hand& player_hand,
                                domain::Deck& deck,
                                const string& player_name,
                                const int dealer_hand_valueall,
                                int& player_hand_valueall) {
  string player_choice_nextcard;

  cout << "Moechtest du noch eine Karte nehmen (Ja oder Nein)?" << endl;
  cin >> player_choice_nextcard;
  cout << "----------------------------------------------------------" << endl;

  transform(player_choice_nextcard.begin(), player_choice_nextcard.end(), player_choice_nextcard.begin(), ::tolower);
  if (player_choice_nextcard != "ja") {
    return false;
  }

  const domain::Card player_hand_newcard = deck.draw();
  player_hand.addCard(player_hand_newcard);

  player_hand_valueall = player_hand.value();

  cout << player_name << "s aktueller Handwert: " << player_hand_valueall << endl;
  cout << "Dealers aktueller Handwert: " << dealer_hand_valueall << endl;

  cout << player_name << "s aktuelle optische Hand:" << endl;
  build_hand_player(player_hand_newcard);

  if (player_hand_valueall > 21) {
    cout << player_name << " ... Du bist leider ueber 21..." << endl;
  }

  return true;
}

int BlackJack::result_game(const int value_player, const int value_dealer) {
  cout << "----------------------------------------------------------" << endl;
  if (value_dealer < 0 || value_player < 0) {
    return 0;
  }
  if (value_dealer > 21 && value_player <= 21) {
    return 2;
  }

  if (value_player > 21 && value_dealer <= 21) {
    return 1;
  }

  if (value_player > 21 && value_dealer > 21) {
    return 3;
  }

  if (value_player == value_dealer) {
    return 4;
  }

  if (value_player > value_dealer) {
    return 2;
  }
  return 1;
}

void BlackJack::build_hand_player(const domain::Card& card) {
  g_playerRenderedHand.push_back(toPrintableCard(card));
  ConsoleRenderer renderer;
  renderer.printCards(g_playerRenderedHand);
}

void BlackJack::build_hand_dealer(const domain::Card& card) {
  g_dealerRenderedHand.push_back(toPrintableCard(card));
  ConsoleRenderer renderer;
  renderer.printCards(g_dealerRenderedHand);
}

void BlackJack::print_hand(const domain::Hand& hand) {
  std::vector<std::pair<std::string, std::string>> cards;
  for (const domain::Card& card : hand.cards()) {
    cards.push_back(toPrintableCard(card));
  }

  ConsoleRenderer renderer;
  renderer.printCards(cards);
}

void BlackJack::clear_rendered_hands() {
  g_playerRenderedHand.clear();
  g_dealerRenderedHand.clear();
}

void BlackJack::rules_bj() {
  printBigText("Regeln BJ");
  std::cout << "|====| Allgemeines Ziel |====|" << std::endl;
  std::cout << "1. Ziel des Spiels ist es, so nah wie moeglich an 21 Punkte zu kommen." << std::endl;
  std::cout << "2. Wer mehr als 21 Punkte hat, verliert automatisch (Bust)." << std::endl;

  std::cout << std::endl << "|====| Kartenwerte |====|" << std::endl;
  std::cout << "3. Zahlenkarten zaehlen entsprechend ihrem Zahlenwert (z. B. 2- 10)." << std::endl;
  std::cout << "4. Bube, Dame und Koenig zaehlen jeweils 10 Punkte." << std::endl;
  std::cout << "5. Das Ass zaehlt 1 oder 11 Punkte - je nachdem, was guenstiger ist." << std::endl;

  std::cout << std::endl << "|====| Spielverlauf |====|" << std::endl;
  std::cout << "6. Jeder Spieler erhaelt zu Beginn zwei Karten." << std::endl;
  std::cout << "7. Der Spieler entscheidet, ob er eine weitere Karte zieht ('Hit') oder keine mehr ('Stand')." << std::endl;
  std::cout << "8. Das Ziel ist, naeher an 21 zu kommen als der Dealer, ohne sie zu ueberschreiten." << std::endl;
  std::cout << "9. Ein Blackjack besteht aus Ass + 10er-Karte mit den ersten beiden Karten und schlaegt alle anderen Kombinationen." << std::endl;

  std::cout << std::endl << "|====| Dealer-Regeln |====|" << std::endl;
  std::cout << "10. Der Dealer spielt zuletzt." << std::endl;
  std::cout << "11. Der Dealer muss bei 16 oder weniger Punkten Karten ziehen." << std::endl;
  std::cout << "12. Der Dealer muss bei 17 oder mehr Punkten stoppen." << std::endl;
  std::cout << "13. In einigen Varianten zieht der Dealer auch bei 'Soft 17' (z.B Ass + 6)." << std::endl;

  std::cout << std::endl << "|====| Spieler-Optionen |====|" << std::endl;
  std::cout << "14. Double Down: Einsatz verdoppeln und genau eine weitere Karte ziehen." << std::endl;
  std::cout << "(Nicht verfuegbar!) 15. Split: Zwei gleichwertige Karten in zwei Haende aufteilen (mit zusaetzlichem Einsatz)." << std::endl;
  std::cout << "    - Nach dem Split von Assen ist meist nur eine Karte pro Hand erlaubt." << std::endl;
  std::cout << "(Nicht verfuegbar!) 16. Surrender: In manchen Varianten kann man aufgeben und verliert nur die Haelfte des Einsatzes." << std::endl;

  std::cout << std::endl << "|====| Versicherung |====|" << std::endl;
  std::cout << "17. Wenn der Dealer ein Ass zeigt, kann man eine Versicherung abschliessen." << std::endl;
  std::cout << "    - Die Versicherung kostet die Haelfte des urspruenglichen Einsatzes." << std::endl;
  std::cout << "    - Hat der Dealer einen Blackjack, zahlt die Versicherung 2:1." << std::endl;

  std::cout << std::endl << "|====| Gewinn & Verlust |====|" << std::endl;
  std::cout << "18. Wer naeher an 21 ist als der Dealer, gewinnt und verdoppelt seinen Einsatz." << std::endl;
  std::cout << "19. Ein Blackjack zahlt mehr Gewinn (3:2 z. B. 15 EUR Gewinn bei 10 EUR Einsatz)." << std::endl;
  std::cout << "20. Bei Punktegleichstand bleibt der Einsatz erhalten." << std::endl;

  std::cout << "===============================" << std::endl;
  cin >> usless_choice;
}

void BlackJack::printexample_bj() {
  ConsoleRenderer renderer;
  std::vector<std::pair<std::string, std::string>> hand = {
      {"A", "\xe2\x99\xa0"},
      {"K", "\xe2\x99\xa0"},
      {"D", "\xe2\x99\xa0"},
      {"J", "\xe2\x99\xa0"},
  };

  renderer.printCards(hand, 1);
}


