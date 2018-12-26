//
//  human_player.hpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#ifndef human_player_hpp
#define human_player_hpp

#include "player.hpp"

class HumanPlayer: public Player {
public:
    HumanPlayer(string, Color);
    Position select_move(Board, int);
    void on_game_end();
};

#endif /* human_player_hpp */
