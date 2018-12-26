//
//  player.cpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//


#include "player.hpp"
#include "position.hpp"
#include "human_player.hpp"

Player::Player(string name, Color color) :
name(name), color(color) {
}

string Player::get_name() {
    return name;
}

Color Player::get_color() {
    return color;
}

Color Player::get_other_color() {
    if (color == white) {
        return black;
    }
    return white;
}

HumanPlayer::HumanPlayer(string name, Color color) :
Player(name, color) {
}

Position HumanPlayer::select_move(Board board, int move_number) {
    position_set legal_moves = board.get_legal_moves(get_color());
    int row = -1, col = -1;
    do {
        cout << "Please enter your " << get_color() << " move, " << get_name()
        << ":";
        cin >> row >> col;
    } while (legal_moves.find(Position(row, col)) == legal_moves.end());
    return Position(row, col);
}

void HumanPlayer::on_game_end() {
    cout << "Good bye " << get_name() << "!";
}


