//
// Created by Peter on 6/2/2024.
//

#ifndef SNAKE_ASTARSEARCH_H
#define SNAKE_ASTARSEARCH_H


#include "../MoveSet.h"
#include "../Game.h"
#include "AStarNode.h"

class AstarSearch {
public:
    static Direction getNextMove(const Game& game);
    static std::vector<Point> getPath(const Game& game);
    static bool isValidPoint(const Point& point, const Game& game, const std::vector<Point>& path);

private:
    static int getMoveCount(Node node);
    static std::vector<Point> pathOfNode(Node node);
};


#endif //SNAKE_ASTARSEARCH_H
