//
//  player.hpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <string>
#include "board.hpp"

using namespace std;

class Player {
private:
    string name;
    Color color;
public:
    Player(string, Color);
    string get_name();
    Color get_color();
    Color get_other_color();
    virtual Position select_move(Board, int) = 0;
    virtual void on_game_end() = 0;
};

#endif /* player_hpp */
