//
//  othello.hpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#ifndef othello_hpp
#define othello_hpp

#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

#include "minimax.hpp"
#include "human_player.hpp"

class Game {
private:
    Board board;
    Player *player1;
    Player *player2;
public:
    Game(Board, Player*, Player*);
    Board& get_board();
    Player* get_player1();
    Player* get_player2();
    void check_winner();
    void play();
};

#endif
