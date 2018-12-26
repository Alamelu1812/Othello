//
//  main.cpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#include "othello.hpp"
#include <unordered_set>

using namespace std;

int main() {
    Board board;
    MiniMaxPlayer minimax_washington_1("Minimax_Weighted_Eval", black, new WeightedEvaluation(0,10,0,0,0), 3);
    MiniMaxPlayer minimax_washington_2("Minimax_Weighted_Eval", white, new WeightedEvaluation(78.922,0,0,0,0), 3);
    //MiniMaxPlayer minimax_counted_1("Minimax_Counted_Eval", black, new CountedEvaluation(), 2);
    //MiniMaxPlayer minimax_counted_2("Minimax_Counted_Eval", white, new CountedEvaluation(), 2);
    //Game game(board, &minimax_washington_1, &minimax_counted_2);
    Game game(board, &minimax_washington_1, &minimax_washington_2);
    game.play();
    return 0;
}
