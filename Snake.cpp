#include "Snake.h"

MoveResponse Snake::move(Point food, int gameSize) {
    Point head = points.back();
    int newHeadX = head.x;
    int newHeadY = head.y;

    switch (heading) {
        case Up:
            newHeadX--;
            break;
        case Down:
            newHeadX++;
            break;
        case Left:
            newHeadY--;
            break;
        case Right:
            newHeadY++;
            break;
    }

    Point newHead{newHeadX, newHeadY};

    Point tail = points[0];
    points.erase(points.begin());

    if (!isPositionValid(newHead, gameSize)){
        return GameOver;
    }

    points.push_back(newHead);
    if (newHead == food){
        points.insert(points.begin(), tail);
        return AteFood;
    }

    return Normal;
}

bool Snake::isSnakePosition(Point p) const {
    for (const Point& point : points) {
        if (point == p) {
            return true;
        }
    }
    return false;
}

Snake Snake::replaceWithPath(const std::vector<Point>& path) const {
    std::vector<Point> endOfPath;
    if (path.size() > points.size()){
        // replace points with the last part of the path.
        endOfPath = std::vector<Point>(path.end() - path.size(), path.end());
    }
    else{
        std::vector<Point> pointCopy = points;
        for(const Point& p : points){
            endOfPath.push_back(p);
            pointCopy.pop_back();
        }
        endOfPath.insert(endOfPath.end(), pointCopy.begin(), pointCopy.end());
    }

    return {endOfPath};
}



Point Snake::getHeadPosition() const {
    return points.back();
}

bool Snake::isPositionValid(Point& point, int gameSize) const{
    if (isSnakePosition(point))
        return false;

    if (point.x == 0 || point.x == gameSize || point.y == 0 || point.y == gameSize)
        return false;

    return true;
}

Point Snake::getAveragePosition() const {
    int totalX = 0;
    int totalY = 0;
    for(const Point& p : points){
        totalX += p.x;
        totalY += p.y;
    }

    int avgX = totalX / points.size();
    int avgY = totalY / points.size();

    return {avgX, avgY};
}


Snake::Snake(std::vector<Point> otherPoints) {
    points = otherPoints;
    if (otherPoints.empty() || otherPoints.size() == 1)
        heading = Up;

    auto lastMove = points.back() - points[points.size() - 2];
    heading = lastMove.ToDirection();
}