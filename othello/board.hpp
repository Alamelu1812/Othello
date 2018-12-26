//
//  board.hpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//



#include <iostream>
#include "position.hpp"

#ifndef board_hpp
#define board_hpp

#define BOARD_SIZE 8
using namespace std;

enum Color {
    empty, black, white
};

class Board {
private:
    Color **board;
    int white_count;
    int black_count;
public:
    Board();
    ~Board();
    Board(const Board&);
    Color** get_board() const; // Returns a copy of the board, so that the current state cannot be externally/illegally modified
    
    int get_black_count() const;
    int get_white_count() const;
    void print_board();
    void place_disc(Color, Position);
    bool is_in_terminal_position() const;
    
    // Only for evaluating debugging AI algo
    static void print_board(Color** board) {
        cout << "Board:" << endl << endl;
        cout << "  ";
        for (int k = 0; k < BOARD_SIZE; k++) {
            cout << " " << k;
        }
        cout << endl;
        for (int i = 0; i < BOARD_SIZE; i++) {
            cout << i << " ";
            for (int j = 0; j < BOARD_SIZE; j++) {
                char color = board[i][j] == white ? 'W' :
                board[i][j] == black ? 'B' : '.';
                cout << " " << color;
            }
            cout << endl;
        }
    }
    ;
    
    static bool check_valid_index(int position_index) {
        return position_index >= 0 && position_index <= 7;
    }
    ;
    
    static bool check_in_direction(Color** board, Color target_color, int row,
                                   int col, int x_dir, int y_dir) {
        Color opposite = target_color == white ? black : white;
        
        // Check whether we have opposite color in given direction in adjacent block
        if (!check_valid_index(row + x_dir) || !check_valid_index(col + y_dir)
            || board[row + x_dir][col + y_dir] != opposite) {
            return false;
        }
        
        for (int next_row = row + 2 * x_dir, next_col = col + 2 * y_dir;
             check_valid_index(next_row) == true
             && check_valid_index(next_col) == true
             && board[next_row][next_col] != empty; next_row +=
             x_dir, next_col += y_dir) {
            if (board[next_row][next_col] == target_color) {
                return true;
            }
        }
        return false;
    }
    ;
    
    position_set get_legal_moves(Color target);
    
    static position_set get_legal_moves(Color** board, Color target) {
        // Collection of Positions where legal moves possible
        position_set legal_moves;
        
        // Check whether each position can have a legal move
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                // We can place a disc only on an empty block!
                if (board[row][col] != empty) {
                    continue;
                }
                
                // Check in all directions whether we have potential discs can be flipped
                if (check_in_direction(board, target, row, col, 0, 1) == true
                    || check_in_direction(board, target, row, col, 0, -1)
                    == true
                    || check_in_direction(board, target, row, col, 1, 0)
                    == true
                    || check_in_direction(board, target, row, col, -1, 0)
                    == true
                    || check_in_direction(board, target, row, col, 1, -1)
                    == true
                    || check_in_direction(board, target, row, col, -1, 1)
                    == true
                    || check_in_direction(board, target, row, col, -1, -1)
                    == true
                    || check_in_direction(board, target, row, col, 1, 1)
                    == true) {
                    
                    // Add the tested position to the collection of legal_positions
                    legal_moves.insert(Position(row, col));
                }
            }
        }
        return legal_moves;
    }
    ;
    
    static int flip_disc_in_direction(Color** board, Color target, int row,
                                      int col, int x_dir, int y_dir) {
        int next_row = row + x_dir;
        int next_col = col + y_dir;
        
        // Check valid indices:
        if (!check_valid_index(next_row) || !check_valid_index(next_col)
            || board[next_row][next_col] == empty) {
            return 0;
        }
        if (board[next_row][next_col] == target) {
            return 1;
        }
        int discs_flipped = flip_disc_in_direction(board, target, next_row,
                                                   next_col, x_dir, y_dir);
        if (discs_flipped == 0) {
            return 0;
        }
        board[next_row][next_col] = target;
        return discs_flipped + 1;
    }
    ;
    
    static int flip_disc_in_direction_and_count(Color** board, Color target,
                                                int row, int col, int x_dir, int y_dir) {
        int current_discs_flipped = flip_disc_in_direction(board, target, row,
                                                           col, x_dir, y_dir);
        return current_discs_flipped > 0 ? current_discs_flipped - 1 : 0;
    }
    ;
    
    static int place_disc(Color** board, Color target, Position position) {
        
        board[position.get_row()][position.get_column()] = target;
        int total_discs_flipped = 0;
        total_discs_flipped += flip_disc_in_direction_and_count(board, target,
                                                                position.get_row(), position.get_column(), 0, 1);
        total_discs_flipped += flip_disc_in_direction_and_count(board, target,
                                                                position.get_row(), position.get_column(), 0, -1);
        total_discs_flipped += flip_disc_in_direction_and_count(board, target,
                                                                position.get_row(), position.get_column(), 1, 0);
        total_discs_flipped += flip_disc_in_direction_and_count(board, target,
                                                                position.get_row(), position.get_column(), -1, 0);
        total_discs_flipped += flip_disc_in_direction_and_count(board, target,
                                                                position.get_row(), position.get_column(), -1, 1);
        total_discs_flipped += flip_disc_in_direction_and_count(board, target,
                                                                position.get_row(), position.get_column(), 1, -1);
        total_discs_flipped += flip_disc_in_direction_and_count(board, target,
                                                                position.get_row(), position.get_column(), -1, -1);
        total_discs_flipped += flip_disc_in_direction_and_count(board, target,
                                                                position.get_row(), position.get_column(), 1, 1);
        return total_discs_flipped;
    }
    
    static string read_from_asc_left(Color** board, string color) {
        string result("");
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                result += color[board[i][j]];
            }
        }
        
        return result;
    }
    
    static string read_from_desc_left(Color** board, string color) {
        string result("");
        
        for (int i = BOARD_SIZE - 1; i >= 0; i--) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                result += color[board[i][j]];
            }
        }
        
        return result;
    }
    
    static string read_from_asc_right(Color** board, string color) {
        string result("");
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = BOARD_SIZE - 1; j >= 0; j--) {
                result += color[board[i][j]];
            }
        }
        
        return result;
    }
    
    static string read_from_desc_right(Color** board, string color) {
        string result("");
        
        for (int i = BOARD_SIZE - 1; i >= 0; i--) {
            for (int j = BOARD_SIZE - 1; j >= 0; j--) {
                result += color[board[i][j]];
            }
        }
        
        return result;
    }
    
    static string read_from_asc_top(Color** board, string color) {
        string result("");
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                result += color[board[j][i]];
            }
        }
        
        return result;
    }
    
    static string read_from_desc_top(Color** board, string color) {
        string result("");
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = BOARD_SIZE - 1; j >= 0; j--) {
                result += color[board[j][i]];
            }
        }
        
        return result;
    }
    
    static string read_from_asc_bottom(Color** board, string color) {
        string result("");
        
        for (int i = BOARD_SIZE - 1; i >= 0; i--) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                result += color[board[j][i]];
            }
        }
        
        return result;
    }
    
    static string read_from_desc_bottom(Color** board, string color) {
        string result("");
        
        for (int i = BOARD_SIZE - 1; i >= 0; i--) {
            for (int j = BOARD_SIZE - 1; j >= 0; j--) {
                result += color[board[j][i]];
            }
        }
        
        return result;
    }
    
    // This method takes in a board and represents it in string form using (F)or, (A)gainst and (E)mpty
    static string get_board_representation(Board board, Color for_color) {
        string color_code = for_color == black ? "efa" : "eaf";
        string code, current_code;
        Color** grid = board.get_board();
        
        code = read_from_asc_left(grid, color_code);
        
        current_code = read_from_asc_right(grid, color_code);
        code = code.compare(current_code) > 0 ? code : current_code;
        
        current_code = read_from_asc_top(grid, color_code);
        code = code.compare(current_code) > 0 ? code : current_code;
        
        current_code = read_from_asc_bottom(grid, color_code);
        code = code.compare(current_code) > 0 ? code : current_code;
        
        code = read_from_desc_left(grid, color_code);
        code = code.compare(current_code) > 0 ? code : current_code;
        
        current_code = read_from_desc_right(grid, color_code);
        code = code.compare(current_code) > 0 ? code : current_code;
        
        current_code = read_from_desc_top(grid, color_code);
        code = code.compare(current_code) > 0 ? code : current_code;
        
        current_code = read_from_desc_bottom(grid, color_code);
        code = code.compare(current_code) > 0 ? code : current_code;
        
        return code;
    }
};


#endif /* board_hpp */
