//
//  minimax.hpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#ifndef minimax_hpp
#define minimax_hpp

#include "player.hpp"
typedef std::pair<Position, int> minimax_result;

class Evaluation {
public:
    virtual int evaluate(Board, Color, int) = 0;
};

class CountedEvaluation : public Evaluation {
public:
    int evaluate(Board, Color, int);
};

class WeightedEvaluation : public Evaluation {
    int mobility_weight, parity_weight, stability_weight, corner_weight, corner_closeness_weight;
public:
    WeightedEvaluation(int, int, int, int, int);
    int evaluate(Board, Color, int);
};

class ThreePhasedEvaluation : public Evaluation {
    WeightedEvaluation evaluation1, evaluation2, evaluation3;
    int mid_phase_start, end_phase_start;
public:
    ThreePhasedEvaluation(int, int, WeightedEvaluation, WeightedEvaluation, WeightedEvaluation);
    int evaluate(Board, Color, int);
};

class MiniMaxPlayer: public Player {
private:
    int evaluation_depth;
    Evaluation* evaluation;
public:
    MiniMaxPlayer(string, Color, Evaluation*, int);
    Position select_move(Board, int);
    minimax_result minimax(Board, Position, int, int, int, int);
    minimax_result maximin(Board, Position, int, int, int, int);
    minimax_result get_terminal_value(Board, Position);
    void on_game_end();
};

#endif /* minimax_hpp */
