//
//  monte_carlo.cpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#include "monte_carlo.hpp"
#include "human_player.hpp"
#include <unordered_map>
#include <fstream>
#include <sstream>

#define MCTS_MAP_FILE "mcts_map.txt"
#define NUM_SIMULATIONS 50
#define PLAY_SIMULATIONS_THRESHOLD 30

typedef unordered_map<string, pair<int, int> > mcts_map;

class MonteCarloPlayer: public Player {
private:
    
    mcts_map monte_carlo_map;
    bool check_time;
    
    void learn_till_time(Board board);
    
    static mcts_map load_mcts_map() {
        
        mcts_map monte_carlo_map;
        string line;
        ifstream myfile(MCTS_MAP_FILE);
        if (myfile.is_open()) {
            while (getline(myfile, line)) {
                string key, value_w, value_t;
                int wins, total;
                
                stringstream ss(line);
                ss >> key >> value_w >> value_t;
                
                wins = stoi(value_w);
                total = stoi(value_t);
                
                monte_carlo_map[key] = make_pair(wins, total);
                
            }
            myfile.close();
        }
        return monte_carlo_map;
    }
    
    static void store_mcts_map(mcts_map& monte_carlo_map) {
        
        ofstream myfile;
        myfile.open(MCTS_MAP_FILE);
        for (auto it = monte_carlo_map.begin(); it != monte_carlo_map.end();
             it++) {
            myfile << it->first << " " << it->second.first << " "
            << it->second.second << endl;
        }
        myfile.close();
    }
    
    static bool simulateMCTS(Board board, mcts_map& monte_carlo_map,
                             Color for_color, Color against_color) {
        
        string board_code = Board::get_board_representation(board, for_color);
        
        if (board.is_in_terminal_position()) {
            bool result;
            if (for_color == white) {
                result = board.get_white_count() > board.get_black_count();
            } else {
                result = board.get_black_count() > board.get_white_count();
            }
            update_stats(monte_carlo_map, board_code, result);
            return result;
        }
        
        Board child(board);
        auto legal_moves = board.get_legal_moves(for_color);
        
        if (legal_moves.size() > 0) {
            auto random_action = next(legal_moves.begin(), rand() % legal_moves.size());
            child.place_disc(for_color, *random_action);
        }
        
        bool result = !(simulateMCTS(child, monte_carlo_map, against_color,
                                     for_color));
        
        update_stats(monte_carlo_map, board_code, result);
        
        // return the result after negation:
        return result;
    }
    
    static void update_stats(mcts_map& monte_carlo_map, string board_code,
                             bool result) {
        int win, total;
        
        auto it = monte_carlo_map.find(board_code);
        if (it == monte_carlo_map.end()) {
            win = (result ? 1 : 0);
            total = 1;
        } else {
            win = (it->second).first + (result ? 1 : 0);
            total = (it->second).second + 1;
        }
        // Save the state to map:
        monte_carlo_map[board_code] = make_pair(win, total);
    }
    
public:
    MonteCarloPlayer(string, Color);
    MonteCarloPlayer(string, Color, bool);
    Position select_move(Board, int);
    void on_game_end();
    
    void learn(Board);
};
