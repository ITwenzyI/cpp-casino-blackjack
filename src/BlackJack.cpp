//
// Created by Kilian on 13.05.25.
//
#include <iostream>
#include <string>
#include <vector>
#include "BlackJack.h"
#include "KartenPrintAusgabe.h"
#include "BigText.h"
#include "limits"
#include <chrono>
#include <thread>
#include <random>
#include <cctype>    // für std::tolower
#include <algorithm> // für std::transform


using namespace std;
int usless_choice;
void BlackJack::mainmenu_bj() {
  int choice;
  printBigText("BlackJack");
  std::cout << "|====| Main Menü|====|" << std::endl;
  cout << "1. Spiel starten" << endl;
  cout << "2. Regeln" << endl;
  cout << "3. Zurück" << endl;
  cin >> choice;

  switch (choice) {
    case 1: startplay_bj(); break;
    case 2: rules_bj(); break;
    case 3: return;
    default: cout << "Invalid choice" << endl; break;
  }
}


void BlackJack::startplay_bj() {
  KartenPrintAusgabe printer;
  std::vector<int> player_cards;
  std::vector<int> dealer_cards;
  int dealer_hand_newcard = 0;
  int dealer_hand_valueall = 0;

  int player_hand_newcard = 0;
  int player_hand_valueall = 0;
  string player_choice_nextcard;
  std::string player_name;

  cout << "Gebe deinen Benutzernamen ein:" << endl;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // WICHTIG!
  getline(cin, player_name);

  cout << "Willkommen in Blackjack " << player_name << endl;

  cout << "Das Spiel startet..." << endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));

  cout << "Dealers beginn Hand:" << endl;
  printer.printVerdeckteKarten(1);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::this_thread::sleep_for(std::chrono::seconds(1));
  cout << "Dealers aktuelle optische Hand:" << endl;
  dealer_hand_newcard = random_number(2, 14);
  dealer_cards.push_back(dealer_hand_newcard);
  dealer_hand_valueall = calculate_hand_value(dealer_cards);

  build_hand_dealer(dealer_hand_newcard);
  cout << "Dealers aktueller Handwert: " << dealer_hand_valueall << endl;

  std::this_thread::sleep_for(std::chrono::seconds(3));

  cout << "----------------------------------------------------------" << endl;

  //---------------------------------------------------------------
  // Spieler //
  // -------------------------------------------------------------

  cout << player_name << "s aktuelle optische Hand:" << endl;
  for (int i = 0; i < 2; ++i) {
    player_hand_newcard = random_number(2, 14);
    player_cards.push_back(player_hand_newcard);
    build_hand_player(player_hand_newcard);
  }
  player_hand_valueall = calculate_hand_value(player_cards);

  cout << player_name << " aktueller Handwert: " << player_hand_valueall << endl;

  if (player_hand_valueall == 21) {
    cout << player_name << " hat einen BLACKJACK!" << endl;
    cout << player_name << " gewinnt automatisch mit einem Blackjack und bekommt den 1.5-fachen Einsatz zurück." << endl;
    return; // Spiel sofort beenden
  }


  cout << "Dealers aktueller Handwert: " << dealer_hand_valueall << endl;

  while(player_hand_valueall < 21 && player_hand_valueall != 0) {
    player_hand_valueall = nextcard_player(player_cards, player_name, dealer_hand_valueall);
  }

  std::this_thread::sleep_for(std::chrono::seconds(2));

  while (dealer_hand_valueall < 17) {
    cout << "----------------------------------------------------------" << endl;
    cout << "Dealers aktuelle optische Hand:" << endl;

    dealer_hand_newcard = random_number(2, 14);
    dealer_cards.push_back(dealer_hand_newcard);
    dealer_hand_valueall = calculate_hand_value(dealer_cards);

    build_hand_dealer(dealer_hand_newcard);
    cout << "Dealers aktueller Handwert: " << dealer_hand_valueall << endl;

    if (check_value_dealer(dealer_hand_valueall)) {
      cout << "Keine Karte mehr für Dealer!" << endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
  }

  if(player_hand_valueall - 99 > 0) {
    player_hand_valueall = player_hand_valueall - 99;
  }


  switch (result_game(player_hand_valueall, dealer_hand_valueall)) {
    case 1: cout << "\nDer Dealer hat gewonnen mit: " << dealer_hand_valueall << " Punkten!" << endl;
    cout << player_name << " verliert seinen Einsatz leider." << endl;
    cout << "Beim nächsten mal wird es der Gewinn!" << endl;
    break;
    case 2: cout << "\n" << player_name << " hat gewonnen mit: " << player_hand_valueall << " Punkten!" << endl;
    cout << player_name << " bekommt seinen Einsatz 2x zurück." << endl;
    cout << "Glückwunsch zum Sieg!!!" << endl;
    break;
    case 3: cout << "\n" << player_name << " und der Dealer haben beide über 21 Punkte!" << endl;
    cout << "Somit gewinnt niemand und " << player_name << " verliert seinen Einsatz!" << endl;
    cout << "Beim nächsten mal wird es der Gewinn!" << endl;
    break;
    case 4: cout << "\n" << "Unentschieden zwischen " << player_name << " und dem Dealer mit jeweils " << player_hand_valueall << " Punkten!" << endl;
    cout << player_name << " bekommt seinen Einsatz zurück." << endl;
    cout << "Glückwunsch zum Unentschieden!" << endl;
    break;
    default: cerr << "\n" << "Fehler!" << endl; break;
  }

  std::this_thread::sleep_for(std::chrono::seconds(3));

  string ende;
  cout << "\n\nBist du zufrieden?" << endl;
  cin >> ende;
  build_hand_player(0);  // leere Spielerhand
  build_hand_dealer(0);  // leere Dealerhand
}



bool BlackJack::check_value_dealer(const int value_dealer) {
  return value_dealer >= 17;
}


int BlackJack::nextcard_player(std::vector<int>& player_cards, const string& player_name, int dealer_hand_valueall) {
  string player_choice_nextcard;
  int player_hand_newcard = 0;

  cout << "Möchtest du noch eine Karte nehmen (Ja oder Nein)?" << endl;
  cin >> player_choice_nextcard;
  cout << "----------------------------------------------------------" << endl;

  transform(player_choice_nextcard.begin(), player_choice_nextcard.end(), player_choice_nextcard.begin(), ::tolower);
  if (player_choice_nextcard != "ja") {
    return calculate_hand_value(player_cards) + 99;
  }

  player_hand_newcard = random_number(2, 14);
  player_cards.push_back(player_hand_newcard);

  int player_hand_valueall = calculate_hand_value(player_cards);

  cout << player_name << "s aktueller Handwert: " << player_hand_valueall << endl;
  cout << "Dealers aktueller Handwert: " << dealer_hand_valueall << endl;

  cout << player_name << "s aktuelle optische Hand:" << endl;
  build_hand_player(player_hand_newcard);

  if (player_hand_valueall > 21) {
    cout << player_name << " ... Du bist leider über 21..." << endl;
  }

  return player_hand_valueall;
}


int BlackJack::result_game(const int value_player, const int value_dealer) {
  cout << "----------------------------------------------------------" << endl;
  if(value_dealer < 0 || value_player < 0) {
    return 0;
  }
  // Dealer über 21 → Spieler gewinnt
  if (value_dealer > 21 && value_player <= 21)
    return 2;

  // Spieler über 21 → Dealer gewinnt
  if (value_player > 21 && value_dealer <= 21)
    return 1;

  // Beide über 21 → Niemand gewinnt
  if (value_player > 21 && value_dealer > 21)
    return 3;

  // Gleichstand
  if (value_player == value_dealer)
    return 4;

  // Wer näher an 21 ist, gewinnt
  if (value_player > value_dealer)
    return 2; // Spieler gewinnt
  else
    return 1; // Dealer gewinnt

}


void BlackJack::build_hand_player(int value_player) {
  static std::vector<std::pair<std::string, std::string>> builded_hand;

  if (value_player == 0) {
    builded_hand.clear();
    return;
  }

  int random_zeichen = random_number(1, 4);

  if (random_zeichen == 1) {
    switch (value_player) {
      case 2: builded_hand.emplace_back("2", "♠"); break;
      case 3: builded_hand.emplace_back("3", "♠"); break;
      case 4: builded_hand.emplace_back("4", "♠"); break;
      case 5: builded_hand.emplace_back("5", "♠"); break;
      case 6: builded_hand.emplace_back("6", "♠"); break;
      case 7: builded_hand.emplace_back("7", "♠"); break;
      case 8: builded_hand.emplace_back("8", "♠"); break;
      case 9: builded_hand.emplace_back("9", "♠"); break;
      case 10: builded_hand.emplace_back("10", "♠"); break;
      case 11: builded_hand.emplace_back("K", "♠"); break;
      case 12: builded_hand.emplace_back("D", "♠"); break;
      case 13: builded_hand.emplace_back("J", "♠"); break;
      case 14: builded_hand.emplace_back("A", "♠"); break;
      default: builded_hand.emplace_back("F", "♠"); break;
    }
  }

  if (random_zeichen == 2) {
    switch (value_player) {
      case 2: builded_hand.emplace_back("2", "♥"); break;
      case 3: builded_hand.emplace_back("3", "♥"); break;
      case 4: builded_hand.emplace_back("4", "♥"); break;
      case 5: builded_hand.emplace_back("5", "♥"); break;
      case 6: builded_hand.emplace_back("6", "♥"); break;
      case 7: builded_hand.emplace_back("7", "♥"); break;
      case 8: builded_hand.emplace_back("8", "♥"); break;
      case 9: builded_hand.emplace_back("9", "♥"); break;
      case 10: builded_hand.emplace_back("10", "♥"); break;
      case 11: builded_hand.emplace_back("K", "♥"); break;
      case 12: builded_hand.emplace_back("D", "♥"); break;
      case 13: builded_hand.emplace_back("J", "♥"); break;
      case 14: builded_hand.emplace_back("A", "♥"); break;
      default: builded_hand.emplace_back("F", "♥"); break;
    }
  }

  if (random_zeichen == 3) {
    switch (value_player) {
      case 2: builded_hand.emplace_back("2", "♦"); break;
      case 3: builded_hand.emplace_back("3", "♦"); break;
      case 4: builded_hand.emplace_back("4", "♦"); break;
      case 5: builded_hand.emplace_back("5", "♦"); break;
      case 6: builded_hand.emplace_back("6", "♦"); break;
      case 7: builded_hand.emplace_back("7", "♦"); break;
      case 8: builded_hand.emplace_back("8", "♦"); break;
      case 9: builded_hand.emplace_back("9", "♦"); break;
      case 10: builded_hand.emplace_back("10", "♦"); break;
      case 11: builded_hand.emplace_back("K", "♦"); break;
      case 12: builded_hand.emplace_back("D", "♦"); break;
      case 13: builded_hand.emplace_back("J", "♦"); break;
      case 14: builded_hand.emplace_back("A", "♦"); break;
      default: builded_hand.emplace_back("F", "♦"); break;
    }
  }

  if (random_zeichen == 4) {
    switch (value_player) {
      case 2: builded_hand.emplace_back("2", "♣"); break;
      case 3: builded_hand.emplace_back("3", "♣"); break;
      case 4: builded_hand.emplace_back("4", "♣"); break;
      case 5: builded_hand.emplace_back("5", "♣"); break;
      case 6: builded_hand.emplace_back("6", "♣"); break;
      case 7: builded_hand.emplace_back("7", "♣"); break;
      case 8: builded_hand.emplace_back("8", "♣"); break;
      case 9: builded_hand.emplace_back("9", "♣"); break;
      case 10: builded_hand.emplace_back("10", "♣"); break;
      case 11: builded_hand.emplace_back("K", "♣"); break;
      case 12: builded_hand.emplace_back("D", "♣"); break;
      case 13: builded_hand.emplace_back("J", "♣"); break;
      case 14: builded_hand.emplace_back("A", "♣"); break;
      default: builded_hand.emplace_back("F", "♣"); break;
    }
  }


  print_hand(builded_hand);
}

void BlackJack::build_hand_dealer(int value_dealer) {
  static std::vector<std::pair<std::string, std::string>> builded_hand_dealer;

  if (value_dealer == 0) {
    builded_hand_dealer.clear();
    return;
  }

  int random_zeichen = random_number(1, 4);

  if (random_zeichen == 1) {
    switch (value_dealer) {
      case 2: builded_hand_dealer.emplace_back("2", "♠"); break;
      case 3: builded_hand_dealer.emplace_back("3", "♠"); break;
      case 4: builded_hand_dealer.emplace_back("4", "♠"); break;
      case 5: builded_hand_dealer.emplace_back("5", "♠"); break;
      case 6: builded_hand_dealer.emplace_back("6", "♠"); break;
      case 7: builded_hand_dealer.emplace_back("7", "♠"); break;
      case 8: builded_hand_dealer.emplace_back("8", "♠"); break;
      case 9: builded_hand_dealer.emplace_back("9", "♠"); break;
      case 10: builded_hand_dealer.emplace_back("10", "♠"); break;
      case 11: builded_hand_dealer.emplace_back("K", "♠"); break;
      case 12: builded_hand_dealer.emplace_back("D", "♠"); break;
      case 13: builded_hand_dealer.emplace_back("J", "♠"); break;
      case 14: builded_hand_dealer.emplace_back("A", "♠"); break;
      default: builded_hand_dealer.emplace_back("F", "♠"); break;
    }
  }

  if (random_zeichen == 2) {
    switch (value_dealer) {
      case 2: builded_hand_dealer.emplace_back("2", "♥"); break;
      case 3: builded_hand_dealer.emplace_back("3", "♥"); break;
      case 4: builded_hand_dealer.emplace_back("4", "♥"); break;
      case 5: builded_hand_dealer.emplace_back("5", "♥"); break;
      case 6: builded_hand_dealer.emplace_back("6", "♥"); break;
      case 7: builded_hand_dealer.emplace_back("7", "♥"); break;
      case 8: builded_hand_dealer.emplace_back("8", "♥"); break;
      case 9: builded_hand_dealer.emplace_back("9", "♥"); break;
      case 10: builded_hand_dealer.emplace_back("10", "♥"); break;
      case 11: builded_hand_dealer.emplace_back("K", "♥"); break;
      case 12: builded_hand_dealer.emplace_back("D", "♥"); break;
      case 13: builded_hand_dealer.emplace_back("J", "♥"); break;
      case 14: builded_hand_dealer.emplace_back("A", "♥"); break;
      default: builded_hand_dealer.emplace_back("F", "♥"); break;
    }
  }

  if (random_zeichen == 3) {
    switch (value_dealer) {
      case 2: builded_hand_dealer.emplace_back("2", "♦"); break;
      case 3: builded_hand_dealer.emplace_back("3", "♦"); break;
      case 4: builded_hand_dealer.emplace_back("4", "♦"); break;
      case 5: builded_hand_dealer.emplace_back("5", "♦"); break;
      case 6: builded_hand_dealer.emplace_back("6", "♦"); break;
      case 7: builded_hand_dealer.emplace_back("7", "♦"); break;
      case 8: builded_hand_dealer.emplace_back("8", "♦"); break;
      case 9: builded_hand_dealer.emplace_back("9", "♦"); break;
      case 10: builded_hand_dealer.emplace_back("10", "♦"); break;
      case 11: builded_hand_dealer.emplace_back("K", "♦"); break;
      case 12: builded_hand_dealer.emplace_back("D", "♦"); break;
      case 13: builded_hand_dealer.emplace_back("J", "♦"); break;
      case 14: builded_hand_dealer.emplace_back("A", "♦"); break;
      default: builded_hand_dealer.emplace_back("F", "♦"); break;
    }
  }

  if (random_zeichen == 4) {
    switch (value_dealer) {
      case 2: builded_hand_dealer.emplace_back("2", "♣"); break;
      case 3: builded_hand_dealer.emplace_back("3", "♣"); break;
      case 4: builded_hand_dealer.emplace_back("4", "♣"); break;
      case 5: builded_hand_dealer.emplace_back("5", "♣"); break;
      case 6: builded_hand_dealer.emplace_back("6", "♣"); break;
      case 7: builded_hand_dealer.emplace_back("7", "♣"); break;
      case 8: builded_hand_dealer.emplace_back("8", "♣"); break;
      case 9: builded_hand_dealer.emplace_back("9", "♣"); break;
      case 10: builded_hand_dealer.emplace_back("10", "♣"); break;
      case 11: builded_hand_dealer.emplace_back("K", "♣"); break;
      case 12: builded_hand_dealer.emplace_back("D", "♣"); break;
      case 13: builded_hand_dealer.emplace_back("J", "♣"); break;
      case 14: builded_hand_dealer.emplace_back("A", "♣"); break;
      default: builded_hand_dealer.emplace_back("F", "♣"); break;
    }
  }
  print_hand(builded_hand_dealer);
}


void BlackJack::print_hand(const std::vector<std::pair<std::string, std::string>> &hand) {
  KartenPrintAusgabe printer;
  printer.printCards(hand);
}

int BlackJack::calculate_hand_value(const std::vector<int>& cards) {
  int total = 0;
  int aces = 0; // asses aber besser

  for (int card : cards) {
    if (card == 14) {
      total += 11;
      aces++;
    } else if (card > 10) {
      total += 10;
    } else {
      total += card;
    }
  }

  while (total > 21 && aces > 0) {
    total -= 10; // Zähle ein Ass als 1 statt 11
    aces--;
  }

  return total;
}



int BlackJack::random_number(int anfang, int ende) {
  std::random_device rd;                              // Zufallsquelle
  std::mt19937 gen(rd());                             // Mersenne Twister Generator
  std::uniform_int_distribution<> dist(anfang, ende);        // Gleichverteilung von Anfang bis Ende
  int zufallszahl = dist(gen);

  return zufallszahl;
}


void BlackJack::rules_bj() {
  printBigText("Regeln BJ");
  std::cout << "|====| Allgemeines Ziel |====|" << std::endl;
  std::cout << "1. Ziel des Spiels ist es, so nah wie möglich an 21 Punkte zu kommen." << std::endl;
  std::cout << "2. Wer mehr als 21 Punkte hat, verliert automatisch (Bust)." << std::endl;

  std::cout << std::endl << "|====| Kartenwerte |====|" << std::endl;
  std::cout << "3. Zahlenkarten zählen entsprechend ihrem Zahlenwert (z. B. 2–10)." << std::endl;
  std::cout << "4. Bube, Dame und König zählen jeweils 10 Punkte." << std::endl;
  std::cout << "5. Das Ass zählt 1 oder 11 Punkte – je nachdem, was günstiger ist." << std::endl;

  std::cout << std::endl << "|====| Spielverlauf |====|" << std::endl;
  std::cout << "6. Jeder Spieler erhält zu Beginn zwei Karten." << std::endl;
  std::cout << "7. Der Spieler entscheidet, ob er eine weitere Karte zieht ('Hit') oder keine mehr ('Stand')." << std::endl;
  std::cout << "8. Das Ziel ist, näher an 21 zu kommen als der Dealer, ohne sie zu überschreiten." << std::endl;
  std::cout << "9. Ein Blackjack besteht aus Ass + 10er-Karte mit den ersten beiden Karten und schlägt alle anderen Kombinationen." << std::endl;

  std::cout << std::endl << "|====| Dealer-Regeln |====|" << std::endl;
  std::cout << "10. Der Dealer spielt zuletzt." << std::endl;
  std::cout << "11. Der Dealer muss bei 16 oder weniger Punkten Karten ziehen." << std::endl;
  std::cout << "12. Der Dealer muss bei 17 oder mehr Punkten stoppen." << std::endl;
  std::cout << "13. In einigen Varianten zieht der Dealer auch bei 'Soft 17' (z.B Ass + 6)." << std::endl;

  std::cout << std::endl << "|====| Spieler-Optionen |====|" << std::endl;
  std::cout << "14. Double Down: Einsatz verdoppeln und genau eine weitere Karte ziehen." << std::endl;
  std::cout << "(Nicht verfügbar!) 15. Split: Zwei gleichwertige Karten in zwei Hände aufteilen (mit zusätzlichem Einsatz)." << std::endl;
  std::cout << "    - Nach dem Split von Assen ist meist nur eine Karte pro Hand erlaubt." << std::endl;
  std::cout << "(Nicht verfügbar!) 16. Surrender: In manchen Varianten kann man aufgeben und verliert nur die Hälfte des Einsatzes." << std::endl;

  std::cout << std::endl << "|====| Versicherung |====|" << std::endl;
  std::cout << "17. Wenn der Dealer ein Ass zeigt, kann man eine Versicherung abschließen." << std::endl;
  std::cout << "    - Die Versicherung kostet die Hälfte des ursprünglichen Einsatzes." << std::endl;
  std::cout << "    - Hat der Dealer einen Blackjack, zahlt die Versicherung 2:1." << std::endl;

  std::cout << std::endl << "|====| Gewinn & Verlust |====|" << std::endl;
  std::cout << "18. Wer näher an 21 ist als der Dealer, gewinnt und verdoppelt seinen Einsatz." << std::endl;
  std::cout << "19. Ein Blackjack zahlt mehr Gewinn (3:2 z. B. 15€ Gewinn bei 10 € Einsatz)." << std::endl;
  std::cout << "20. Bei Punktegleichstand bleibt der Einsatz erhalten." << std::endl;

  std::cout << "===============================" << std::endl;
  cin >> usless_choice;
}

void BlackJack::printexample_bj() {
  KartenPrintAusgabe printer;
  //Verfügbare Karten: 2-10 A(1 oder 11), J(Bube), K(König), D(Dame)
  //Verfügbare Zeichen: ♠ ♥ ♦ ♣
  std::vector<std::pair<std::string, std::string>> hand = {
    {"A", "♠"},
    {"K", "♠"},
{"D", "♠"},
{"J", "♠"},
   // {"10", "♥"},
    //{"K", "♦"},
   // {"7", "♣"}
};

  printer.printCards(hand, 1);
  //printer.printVerdeckteKarten(2);
}