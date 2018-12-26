//
//  minimax.cpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#include "minimax.hpp"
#include "player.hpp"
#include <limits.h>

#ifndef MINIMAX_H_
#define MINIMAX_H_

MiniMaxPlayer::MiniMaxPlayer(string name, Color color, Evaluation* evaluation, int evaluation_depth) :
Player(name, color), evaluation(evaluation), evaluation_depth(evaluation_depth) {
}

Position MiniMaxPlayer::select_move(Board board, int move_number) {
    return minimax(board, Position(-1, -1), evaluation_depth, INT_MIN, INT_MAX, move_number).first;
}


bool Board::is_in_terminal_position() const {
    return (BOARD_SIZE * BOARD_SIZE == black_count + white_count)
    || (get_legal_moves(board, white).empty()
        && get_legal_moves(board, black).empty());
}

minimax_result MiniMaxPlayer::get_terminal_value(Board board,
                                                 Position current_action) {
    if (get_color() == white) {
        if (board.get_white_count() > board.get_black_count()) {
            return make_pair(current_action, INT_MAX);
        } else {
            return make_pair(current_action, INT_MIN);
        }
    } else {
        if (board.get_white_count() > board.get_black_count()) {
            return make_pair(current_action, INT_MIN);
        } else {
            return make_pair(current_action, INT_MAX);
        }
    }
}

minimax_result MiniMaxPlayer::minimax(Board board, Position current_action,
                                      int depth, int alpha, int beta, int move_number) {
    if (board.is_in_terminal_position()) {
        return get_terminal_value(board, current_action);
    }
    
    if (depth == 0) {
    //cout<<"\n Minimax "<<evaluation->evaluate(board, get_color(), move_number)<<" for color"<<get_color();
    cout<<"\n Minimax Current action "<<current_action.get_row()<<" "<<current_action.get_column()<<" evaluation "<<evaluation->evaluate(board, get_color(), move_number);
     return make_pair(current_action,
     evaluation->evaluate(board, get_color(), move_number));
     }
    
    int value = INT_MIN;
    Position best_action = current_action;
    position_set actions = board.get_legal_moves(get_color());
    
    for (auto action = actions.begin(); action != actions.end(); action++) {
        Board child(board);
        child.place_disc(get_color(), *action);
        int current_value = maximin(child, current_action, depth - 1,
                                    alpha > value ? alpha : value, beta, move_number + 1).second;
        
        if (current_value >= beta
            && Board::check_valid_index(current_action.get_row()) == true) {
            return make_pair(best_action, value);
        }
        if (current_value > value
            || Board::check_valid_index(current_action.get_row())
            == false) {
            value = current_value;
            best_action = *action;
        }
    }
    //cout<<"\n Executing Minimax";
    cout<<"\n Minimax Best action "<<best_action.get_row()<<" "<<best_action.get_column();
    return make_pair(best_action, value);
}

minimax_result MiniMaxPlayer::maximin(Board board, Position current_action,
                                      int depth, int alpha, int beta, int move_number) {
    if (board.is_in_terminal_position()) {
        return get_terminal_value(board, current_action);
    }
    if (depth == 0) {
        //cout<<"\n Maximin "<<evaluation->evaluate(board, get_other_color(), move_number)<<" for color"<<get_color();
        cout<<"\n Maximin Current action "<<current_action.get_row()<<" "<<current_action.get_column()<<" evaluation "<<evaluation->evaluate(board, get_other_color(), move_number);
        return make_pair(current_action,
                         evaluation->evaluate(board, get_other_color(), move_number));
    }
    int value = INT_MAX;
    Position best_action = current_action;
    position_set actions = board.get_legal_moves(get_other_color());
    
    for (auto action = actions.begin(); action != actions.end(); action++) {
        Board child(board);
        child.place_disc(get_color(), *action);
        int current_value = minimax(child, current_action, depth - 1, alpha,
                                    beta < value ? beta : value, move_number + 1).second;
        
        if (current_value <= alpha
            && Board::check_valid_index(current_action.get_row()) == true) {
            return make_pair(best_action, value);
        }
        if (current_value < value
            || Board::check_valid_index(current_action.get_row())
            == false) {
            value = current_value;
            best_action = *action;
        }
    }
    //cout<<"\n Executing Maximin";
    cout<<"\n Maximin Best action "<<best_action.get_row()<<" "<<best_action.get_column();
    return make_pair(best_action, value);
}

void MiniMaxPlayer::on_game_end() {
    cout << "Good bye " << get_name() << "!";
}

int CountedEvaluation::evaluate(Board board, Color color, int move_number) {
    if (color == white) {
        return board.get_white_count() - board.get_black_count();
    }
    return board.get_black_count() - board.get_white_count();
}

WeightedEvaluation::WeightedEvaluation(int mobility_weight,
                                       int parity_weight, int stability_weight, int corner_weight, int corner_closeness_weight) :
mobility_weight(mobility_weight), parity_weight(parity_weight), stability_weight(stability_weight), corner_weight(corner_weight), corner_closeness_weight(corner_closeness_weight) {
}

int ThreePhasedEvaluation::evaluate(Board board, Color color, int move_number) {
    if (move_number < mid_phase_start) {
        return evaluation1.evaluate(board, color, move_number);
    }
    if (move_number < end_phase_start) {
        return evaluation2.evaluate(board, color, move_number);
    }
    return evaluation3.evaluate(board, color, move_number);
}

ThreePhasedEvaluation::ThreePhasedEvaluation(int mid_phase_start, int end_phase_start, WeightedEvaluation evaluation1,
                                             WeightedEvaluation evaluation2, WeightedEvaluation evaluation3) : mid_phase_start(mid_phase_start),
end_phase_start(end_phase_start), evaluation1(evaluation1), evaluation2(evaluation2), evaluation3(evaluation1) {
}


int WeightedEvaluation::evaluate(Board board, Color color, int move_number) {
    // TODO: Al to plugin code here
    int overall_evaluation = 0;
    Color opposite = (color==white? black : white);
    
    
    /*
    //Evaluation function based on corner
    
    int my_corner_count = 0;
    int opponent_corner_count = 0;
    int corner_evalaution = 0;
    
    if(board.get_board()[0][0] != empty)
        board.get_board()[0][0] == color? my_corner_count += 1 : opponent_corner_count += 1;
    if(board.get_board()[0][7] != empty)
        board.get_board()[0][7] == color? my_corner_count += 1 : opponent_corner_count += 1;
    if(board.get_board()[7][0] != empty)
        board.get_board()[7][0] == color? my_corner_count += 1 : opponent_corner_count += 1;
    if(board.get_board()[7][7] != empty)
        board.get_board()[7][7] == color? my_corner_count += 1 : opponent_corner_count += 1;
    corner_evalaution = 25 * (my_corner_count - opponent_corner_count);
    
    
    //Evaluation function based on corner closeness
    int my_corner_closeness_count = 0;
    int opponenet_corner_closeness_count = 0;
    int corner_closeness_evaluation = 0;
    
    if(board.get_board()[0][0] == empty)  {
        board.get_board()[0][1] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
        board.get_board()[1][0] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
        board.get_board()[1][1] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
    }
    
    if(board.get_board()[0][7] == empty)  {
        board.get_board()[0][6] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
        board.get_board()[1][6] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
        board.get_board()[1][7] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
    }
    
    if(board.get_board()[7][0] == empty)  {
        board.get_board()[7][1] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
        board.get_board()[6][1] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
        board.get_board()[6][0] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
    }
    
    if(board.get_board()[7][7] == empty)  {
        board.get_board()[6][7] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
        board.get_board()[6][6] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
        board.get_board()[7][6] == color? my_corner_closeness_count+= 1 : opponenet_corner_closeness_count+= 1;
    }
    
    corner_closeness_evaluation = -12.5 * (my_corner_closeness_count - opponenet_corner_closeness_count);
    
    //Evaluation function based on stability
    int row_stability[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int col_stability[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int every_row, every_col;
    int my_stability_count = 0;
    int opponent_stability_count = 0;
    int stability_evaluation = 0;
    
    for(int row_iterator = 0; row_iterator < 8; row_iterator++)
        for(int col_iterator =0; col_iterator < 8; col_iterator++)  {
            if(board.get_board()[row_iterator][col_iterator] != empty)   {
                for(int front_disc_iterator = 0; front_disc_iterator < 8; front_disc_iterator++)  {
                    every_row = row_iterator + row_stability[front_disc_iterator];
                    every_col = col_iterator + col_stability[front_disc_iterator];
                    if(every_row >= 0 && every_row < 8 && every_col >= 0 && every_col < 8 && board.get_board()[every_row][every_col] == empty) {
                        if(board.get_board()[row_iterator][col_iterator] == color)  my_stability_count++;
                        else opponent_stability_count++;
                        break;
                    }
                }
            }
        }
    
    if(my_stability_count > opponent_stability_count)
        stability_evaluation = -(100.0 * my_stability_count)/(my_stability_count + opponent_stability_count);
    else if(my_stability_count < opponent_stability_count)
        stability_evaluation = (100.0 * opponent_stability_count)/(my_stability_count + opponent_stability_count);
    else stability_evaluation = 0;*/
    
    //Evaluation function based on mobility
    
    int my_legal_moves_count = 0;
    int opponent_legal_moves_count = 0;
    int mobility_evaluation = 0;
    
    my_legal_moves_count = Board::get_legal_moves(board.get_board(),color).size();
    opponent_legal_moves_count = Board::get_legal_moves(board.get_board(),opposite).size();
    
    if(my_legal_moves_count > opponent_legal_moves_count)
        mobility_evaluation = (100.0 * my_legal_moves_count)/(my_legal_moves_count + opponent_legal_moves_count);
    else if(my_legal_moves_count < opponent_legal_moves_count)
        mobility_evaluation = -(100.0 * opponent_legal_moves_count)/(my_legal_moves_count + opponent_legal_moves_count);
    else mobility_evaluation = 0;
    
    /*if(mobility_weight != 0){
        cout<<"\n my_legal_moves_count"<<my_legal_moves_count;
        cout<<"\n opponent_legal_moves_count"<<opponent_legal_moves_count;
        cout<<"\n mobility_evaluation"<<mobility_evaluation;
        cout<<"\n mobility_weight"<<mobility_weight;
    }
    cout<<"\n mobility_weight"<<mobility_weight;*/
    //Evaluation function based on disc count
    
    int my_disc_count = 0;
    int opponent_disc_count = 0;
    int disc_count_evaluation;
    
    my_disc_count = (color == white? board.get_white_count() : board.get_black_count());
    opponent_disc_count = (opposite == white? board.get_white_count() : board.get_black_count());
    
    if(my_disc_count > opponent_disc_count)
        disc_count_evaluation = (100.0 * my_disc_count)/(my_disc_count + opponent_disc_count);
    else if(my_disc_count < opponent_disc_count)
        disc_count_evaluation = -(100.0 * opponent_disc_count)/(my_disc_count + opponent_disc_count);
    else disc_count_evaluation = 0;
    
    /*if(parity_weight != 0){
        cout<<"\n my_disc_count"<<my_disc_count;
        cout<<"\n opponent_disc_count"<<opponent_disc_count;
        cout<<"\n parity_evaluation"<<disc_count_evaluation;
        cout<<"\n parity weight"<<parity_weight;
    }*/
    
    //cout<<"\n Disc count"<<my_disc_count<<" "<<opponent_disc_count;
    
    //cout<<mobility_weight<<parity_weight<<stability_weight<<corner_weight<<corner_closeness_weight;
    
    //if (color == black)
        //cout<<"\nparity contribution"<<(parity_weight * disc_count_evaluation);
    
    /*cout<<"\nParity contribution"<<(parity_weight * disc_count_evaluation)<<"for color "<<color;
    cout<<"\nMobility contribution"<<(mobility_weight * mobility_evaluation)<<"for color "<<color<<"\n";
     */
    
    //Computing overall evaluation function

    //overall_evaluation = (parity_weight * disc_count_evaluation)+(corner_weight * corner_evalaution) + (mobility_weight * mobility_evaluation) + (corner_closeness_weight * corner_closeness_evaluation) + (stability_weight * stability_evaluation);
    overall_evaluation = (parity_weight * disc_count_evaluation) + (mobility_weight * mobility_evaluation);
    //cout<<"\nOverall evaluation function value="<<overall_evaluation<<"\n";
    //cout<<"\nDisc Count evaluation function value="<<disc_count_evaluation<<"\n";
    //cout<<"\nMobility evaluation function value="<<mobility_evaluation<<"\n";
    //cout<<"\nStability evaluation function value="<<stability_evaluation<<"\n";
    //cout<<"\n Overall evaluation="<<overall_evaluation<<"Mobility="<<(mobility_weight * mobility_evaluation)<<"Parity="<<(parity_weight * disc_count_evaluation);
    return overall_evaluation;

}
 

#endif /* MINIMAX_H_ */

