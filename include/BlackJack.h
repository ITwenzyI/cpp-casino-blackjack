//
// Created by Kilian on 13.05.25.
//

#ifndef BLACKJACK_H
#define BLACKJACK_H

class BlackJack {
  public:
    void mainmenu_bj();
    void startplay_bj();
    void rules_bj();
    static bool check_value_dealer(int value_dealer);
    int nextcard_player(int player_hand_valueall, int player_hand_value, const std::string& player_name, int dealer_hand_valueall);
    int result_game(int value_player, int value_dealer);
    int random_number(int anfang, int ende);
    void print_hand(const std::vector<std::pair<std::string, std::string>> &hand);
    void build_hand_player(int value_player);
    void build_hand_dealer(int value_dealer);
    void printexample_bj();
};

#endif //BLACKJACK_H
