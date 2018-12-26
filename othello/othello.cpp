//
//  othello.cpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#include "othello.hpp"

Game::Game(Board board, Player *p1, Player *p2) :
board(board), player1(p1), player2(p2) {
}

Board& Game::get_board() {
    return board;
}

Player* Game::get_player1() {
    return player1;
}

Player* Game::get_player2() {
    return player2;
}

void Game::check_winner() {
    if (board.get_white_count() == board.get_black_count()) {
        //Tie
        cout << "It's a tie!!!";
    } else if (board.get_white_count() > board.get_black_count()) {
        //White wins
        if (player1->get_color() == white) {
            cout << player1->get_name() << " (white) wins!!!";
        } else {
            cout << player2->get_name() << " (black) wins!!!";
        }
    } else if (player1->get_color() == black) {
        cout << player1->get_name() << " (black) wins!!!";
    } else {
        cout << player2->get_name() << " (white) wins!!!";
    }
    cout<< "\n Black count" <<board.get_black_count();
    cout<< "\n White count" <<board.get_white_count()<<"\n";
}

void Game::play() {
    cout << "Game starts......" << endl;
    //alternate turns
    //accept move - evaluate
    //implement move
    
    //Initial Board position
    board.print_board();
    
    //Check player with black color if disc
    int turn = 0; //turn indicates player number to play
    int move_number = 0;
    if (player1->get_color() == black) {
        turn = 1;
    } else {
        turn = 2;
    }
    
    while (!board.is_in_terminal_position()) {
        
        if (turn == 1) {
            if (board.get_legal_moves(player1->get_color()).size() > 0) {
                Position disc_position = player1->select_move(board, ++move_number);
                cout << player1->get_name() << " placing disc at Position("
                << disc_position.get_row() << ","
                << disc_position.get_column() << ")" << endl;
                board.place_disc(player1->get_color(), disc_position);
            }
            turn = 2;
        } else {
            if (board.get_legal_moves(player2->get_color()).size() > 0) {
                Position disc_position = player2->select_move(board, ++move_number);
                cout << player2->get_name() << " placing disc at Position("
                << disc_position.get_row() << ","
                << disc_position.get_column() << ")" << endl;
                board.place_disc(player2->get_color(), disc_position);
            }
            turn = 1;
        }
        board.print_board();
    }
    cout<<"Game finished in "<<move_number<<" moves"<<endl;
    check_winner();
    player1->on_game_end();
    player2->on_game_end();
}



