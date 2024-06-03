//
// Created by Peter on 6/1/2024.
//

#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "Game.h"

class Display {
public:
    void displayGame(Game& game, Direction lastMove);
    void displayLostScreen(int score);

private:
    std::string renderGame(Game& game, Direction lastMove);
    void updateScreenBuffer(const std::string& newDisplay);
    void clearScreen();
    void printScreen();

    std::vector<std::string> screenBuffer;
};


#endif //SNAKE_DISPLAY_H
