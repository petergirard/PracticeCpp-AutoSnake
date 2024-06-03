//
// Created by Peter on 6/1/2024.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H


#include <vector>
#include "Point.h"
#include "Direction.h"
#include "MoveResponse.h"

class Snake {
public:
    std::vector<Point> points;
    Direction heading;
    Snake(int x, int y){
        points.push_back(Point{x, y});
        heading = Up;
    };

    MoveResponse move(Point food, int gameSize);
    bool isSnakePosition(Point p) const;
    Snake replaceWithPath(const std::vector<Point>& path) const;
    Point getHeadPosition() const;
    Point getAveragePosition() const;
    Snake copy() const { return Snake{*this}; }
    void removeTail();

private:
    Snake(Snake const &other){
        points = other.points;
        heading = other.heading;
    }

    Snake(std::vector<Point> otherPoints);

    bool isPositionValid(Point& point, int gameSize) const;
};


#endif //SNAKE_SNAKE_H
