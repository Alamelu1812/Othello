//
//  poistion.hpp
//  othello_2
//
//  Created by Alamelu Murugappan on 5/12/18.
//  Copyright © 2018 Alamelu Velappan Subramanian. All rights reserved.
//

#ifndef poistion_hpp
#define poistion_hpp

#include <unordered_set>
using namespace std;

class Position {
private:
    int row, col;
public:
    Position (int, int);
    int get_row() const;
    int get_column() const;
};

struct PositionComparator {
    bool operator()(const Position & left, const Position & right) const {
        if ((left.get_row() == right.get_row()) && (left.get_column() == right.get_column()))
            return true;
        return false;
    }
};

struct PositionHasher {
    size_t operator()(const Position & obj) const {
        return std::hash<int>()(obj.get_row() * 10 + obj.get_column());
    }
};

typedef unordered_set<Position, PositionHasher, PositionComparator> position_set;

#endif /* poistion_hpp */
