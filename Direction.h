//
// Created by Peter on 6/1/2024.
//

#ifndef SNAKE_DIRECTION_H
#define SNAKE_DIRECTION_H


enum Direction{
    None,
    Up,
    Down,
    Left,
    Right
};

inline const char* ToString(Direction direction)
{
    switch (direction)
    {
        case Up: return "Up";
        case Down: return "Down";
        case Left: return "Left";
        case Right: return "Right";
        case None: return "None";
    }
}

#endif //SNAKE_DIRECTION_H
