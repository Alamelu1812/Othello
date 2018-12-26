//
//  board.cpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#include "board.hpp"

Board::Board() {
    
    board = new Color*[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = new Color[BOARD_SIZE];
    }
    
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = empty;
        }
    }
    
    // Place initial discs:
    board[3][3] = white;
    board[4][4] = white;
    board[3][4] = black;
    board[4][3] = black;
    white_count = 2;
    black_count = 2;
}

Board::Board(const Board& source) {
    
    white_count = source.get_white_count();
    black_count = source.get_black_count();
    
    board = new Color*[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[i] = new Color[BOARD_SIZE];
    }
    
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = source.board[row][col];
        }
    }
}

Board::~Board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        delete board[i];
    }
    delete board;
}

int Board::get_black_count() const {
    return black_count;
}

int Board::get_white_count() const {
    return white_count;
}

Color** Board::get_board() const {
    return board;
}

void Board::print_board() {
    print_board(board);
}

void Board::place_disc(Color color, Position position) {
    int total_discs_flipped = Board::place_disc(board, color, position);
    if (color == white) {
        white_count = white_count + 1 + total_discs_flipped;
        black_count -= total_discs_flipped;
    } else {
        black_count = black_count + 1 + total_discs_flipped;
        white_count -= total_discs_flipped;
    }
}

position_set Board::get_legal_moves(Color target) {
    return Board::get_legal_moves(board, target);
}

