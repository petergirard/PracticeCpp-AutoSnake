//
// Created by Peter on 6/2/2024.
//

#ifndef SNAKE_MOVESET_H
#define SNAKE_MOVESET_H


#include "Direction.h"
#include <utility>
#include <vector>

class MoveSet {

public:
    Direction nextMove();
    explicit MoveSet(std::vector<Direction> moves) : moves(std::move(moves)) {}

private:
    std::vector<Direction> moves;
};


#endif //SNAKE_MOVESET_H
