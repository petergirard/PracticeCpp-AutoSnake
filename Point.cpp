//
// Created by Peter on 6/1/2024.
//

#include <valarray>
#include "Point.h"

Point Point::operator+(const Point& p) const {
    return {x + p.x, y + p.y};
}


Point Point::operator-(const Point &p) const {
    return Point(x - p.x, y - p.y);
}

bool Point::operator==(const Point& p) const {
    return x == p.x && y == p.y;
}

int Point::distanceManhattan(const Point &p) const {
    return std::abs(x - p.x) +
            std::abs(y - p.y);
}

float Point::distanceEuclidean(const Point &p) const {
    return std::sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

Direction Point::ToDirection() const {
    if (x == 0 && y == 1)
        return Right;
    if (x ==0 && y == -1)
        return Left;
    if (x == 1 && y == 0)
        return Down;
    if (x ==-1 && y == 0)
        return Up;

    return None;
}
