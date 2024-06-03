//
// Created by Peter on 6/1/2024.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H


#include "Snake.h"

class Game {

public:
    explicit Game(int size,
                  int snakeX,
                  int snakeY,
                  int foodX,
                  int foodY)
                  : size(size),
                  snake(snakeX, snakeY),
                  food(foodX, foodY){
        playing = true;
    }
    bool playing;
    Snake snake;
    Point food;
    int size;
};


#endif //SNAKE_GAME_H
