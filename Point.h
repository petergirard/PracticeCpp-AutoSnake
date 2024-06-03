//
// Created by Peter on 6/1/2024.
//

#ifndef SNAKE_POINT_H
#define SNAKE_POINT_H


#include "Direction.h"

class Point {
public:
    int x;
    int y;

    Point(int x1, int y1) : x(x1), y(y1) {}
    Point operator+(const Point& p) const;
    Point operator-(const Point& p) const;
    bool operator==(const Point& p) const;

    int distanceManhattan(const Point& p) const;
    float distanceEuclidean(const Point& p) const;
    Direction ToDirection() const;
};


#endif //SNAKE_POINT_H
