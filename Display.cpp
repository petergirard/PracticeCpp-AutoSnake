#include <iostream>
#include <thread>
#include "Display.h"
#include "Game.h"
using namespace std;

// NOTE: All buffer logic is from ChatGPT.

void Display::displayGame(Game& game, Direction lastMove) {
    std::string newDisplay = renderGame(game, lastMove);
    updateScreenBuffer(newDisplay);
    printScreen();
}

void Display::displayLostScreen(int score) {
    // Move cursor to the end of the current screen
    std::cout << "\033[" << screenBuffer.size() + 1 << ";1H";
    std::cout << "Game Over! You got " << score << " points" << std::endl;
}

std::string Display::renderGame(Game& game, Direction lastMove) {
    std::string gameDisplay;

    for (int x = 0; x <= game.size; x++) {
        for (int y = 0; y <= game.size; y++) {
            if (x == 0 || x == game.size) {
                gameDisplay += "# ";
            } else if (y == 0 || y == game.size) {
                gameDisplay += "# ";
            } else if (game.snake.isSnakePosition(Point{x, y})) {
                gameDisplay += "o ";
            } else if (x == game.food.x && y == game.food.y) {
                gameDisplay += "X ";
            } else {
                gameDisplay += "  ";
            }
        }
        gameDisplay += "\n";
    }
    gameDisplay += "\n Last Move = ";
    gameDisplay += ToString(lastMove);
    gameDisplay += "\n";

    return gameDisplay;
}

void Display::updateScreenBuffer(const std::string& newDisplay) {
    // Split the newDisplay into lines
    std::vector<std::string> newBuffer;
    size_t pos = 0, end;
    while ((end = newDisplay.find('\n', pos)) != std::string::npos) {
        newBuffer.push_back(newDisplay.substr(pos, end - pos));
        pos = end + 1;
    }

    // Update the screen buffer with only changed lines
    for (size_t i = 0; i < newBuffer.size(); ++i) {
        if (i >= screenBuffer.size() || screenBuffer[i] != newBuffer[i]) {
            if (i < screenBuffer.size()) {
                screenBuffer[i] = newBuffer[i];
            } else {
                screenBuffer.push_back(newBuffer[i]);
            }
            // Move the cursor to the correct position and print the updated line
            std::cout << "\033[" << i + 1 << ";1H" << newBuffer[i];
        }
    }

    // Clear any extra lines from the previous frame
    if (screenBuffer.size() > newBuffer.size()) {
        for (size_t i = newBuffer.size(); i < screenBuffer.size(); ++i) {
            std::cout << "\033[" << i + 1 << ";1H" << std::string(screenBuffer[i].size(), ' ');
        }
        screenBuffer.resize(newBuffer.size());
    }
}

void Display::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void Display::printScreen() {
    std::flush(std::cout);
}


