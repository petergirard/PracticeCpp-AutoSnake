//
// Created by Peter on 6/2/2024.
//

#ifndef SNAKE_ASTARNODE_H
#define SNAKE_ASTARNODE_H

#include "../Point.h"

struct Node{
    Point position;
    float g; // Cost from the start node to this node
    float h; // Heuristic (estimated cost from this node to the goal)
    float f; // Total cost (g + h)
    Node* parent; // Pointer to the parent node

    Node(const Point& pos, float g_, float h_, Node* parent_) : position(pos), g(g_), h(h_), f(g_ + h_), parent(parent_) {}

    // Comparison for priority queue.
    bool operator<(const Node& other) const{
        return f > other.f;
    }
};

#endif //SNAKE_ASTARNODE_H
