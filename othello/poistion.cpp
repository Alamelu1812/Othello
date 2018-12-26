//
//  poistion.cpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#include "poistion.hpp"

Position::Position(int row, int col) :
row(row), col(col) {
}

int Position::get_row() const {
    return row;
}

int Position::get_column() const {
    return col;
}
