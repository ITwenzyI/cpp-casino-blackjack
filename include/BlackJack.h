//
// Created by Kilian on 13.05.25.
//
#include <vector>
#include <string>
#include "domain/Card.hpp"
#include "domain/Deck.hpp"
#include "domain/Hand.hpp"

#ifndef BLACKJACK_H
#define BLACKJACK_H

class BlackJack {
  public:
    void mainmenu_bj();
    void startplay_bj();
    void rules_bj();
    static bool check_value_dealer(int value_dealer);
    bool nextcard_player(domain::Hand& player_hand, domain::Deck& deck, const std::string& player_name, int dealer_hand_valueall, int& player_hand_valueall);
    int result_game(int value_player, int value_dealer);
    void print_hand(const domain::Hand& hand);
    void build_hand_player(const domain::Card& card);
    void build_hand_dealer(const domain::Card& card);
    void clear_rendered_hands();
    void printexample_bj();
};

#endif //BLACKJACK_H
