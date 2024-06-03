//
// Created by Peter on 6/2/2024.
//

#include "AstarSearch.h"
#include "AStarNode.h"
#include <vector>
#include <valarray>
#include <queue>


Direction AstarSearch::getNextMove(const Game &game) {
    auto path = getPath(game);
    if (path.empty())
        return None;
    auto firstPoint = path[0];
    auto snakeHead = game.snake.getHeadPosition();
    auto firstMove = firstPoint - snakeHead;
    return firstMove.ToDirection();
}


std::vector<Point> AstarSearch::getPath(const Game &game) {
    const std::vector<Point> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    std::priority_queue<Node> openSet;
    std::vector<Point> closedSet;

    auto start = game.snake.getHeadPosition();
    Node startNode(start, 0, start.distanceManhattan(game.food), nullptr);

    openSet.push(startNode);

    while (!openSet.empty()){
        auto currentNode = openSet.top();
        openSet.pop();

        closedSet.push_back(currentNode.position);

        if (currentNode.position == game.food){
            return pathOfNode(currentNode);
        }

        // Generate neighboring nodes
        for(const auto& dir : directions){
            Point neighborPos = currentNode.position + dir;

            auto pointClosed = std::find(closedSet.begin(), closedSet.end(), neighborPos) != closedSet.end();
            if (AstarSearch::isValidPoint(neighborPos, game, pathOfNode(currentNode)) && !pointClosed){
                float neighborG = currentNode.g + 1;

                // Create a dynamically allocated copy of the currentNode
                Node* parent = new Node(currentNode);

                Node neighborNode(neighborPos, neighborG, neighborPos.distanceManhattan(game.food), parent);
                openSet.push(neighborNode);
            }
        }
    }

    return {};
}

int AstarSearch::getMoveCount(Node node) {
    int count = 0;
    while(node.parent != nullptr){
        count++;
        node = *node.parent;
    }
    return count;
}


bool AstarSearch::isValidPoint(const Point& point, const Game& game, const std::vector<Point>& path) {
    auto isInsideBounds = point.x > 0 && point.x < game.size && point.y > 0 && point.y < game.size;
    auto newSnake = game.snake.replaceWithPath(path);
    newSnake.points.pop_back();
    auto isInsideSnake = newSnake.isSnakePosition(point);
    return isInsideBounds && !isInsideSnake;
}

std::vector<Point> AstarSearch::pathOfNode(Node node) {
    std::vector<Point> path;
    while(node.parent != nullptr){
        path.push_back(node.position);
        node = *node.parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}