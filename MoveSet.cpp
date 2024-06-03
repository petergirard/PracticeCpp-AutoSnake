//
// Created by Peter on 6/2/2024.
//

#include <stdexcept>
#include "MoveSet.h"


Direction MoveSet::nextMove() {
    if (moves.empty()) {
        throw std::out_of_range("No more moves available");
    }
    Direction move = moves.front();
    moves.erase(moves.begin());
    return move;
}


