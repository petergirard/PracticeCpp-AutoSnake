#include <iostream>
#include <chrono>
#include <thread>
#include "Snake.h"
#include "Game.h"
#include "Display.h"
#include <random>
#include "MoveSet.h"
#include "Astar/AstarSearch.h"

#define SIZE 14

void Sleep(int ms);
void InputThread(Game& game);
void GameThread(Game& game);
MoveSet GetNewMoveSet(Game& game);
Direction GetNextMove(Game& game);

int main() {

    Game game{SIZE, 6, 6, 3, 3};
    GameThread(game);
    return 0;
}

void Sleep(int ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


void GameThread(Game& game){
    std::random_device rd;  // Create a random device
    std::mt19937 gen(rd()); // Create a Mersenne Twister pseudo-random number generator

    Display display;
    system("clear");

    Direction lastMove = None;
    while(game.playing){

        auto nextMove = AstarSearch::getNextMove(game);
        if (nextMove != None){
            game.snake.heading = nextMove;
            lastMove = nextMove;
        }

        auto moveResponse = game.snake.move(game.food, SIZE);;

        if (moveResponse == GameOver){
            display.displayGame(game, lastMove);
            display.displayLostScreen(game.snake.points.size());
            game.playing = false;
            return;
        }
        else if (moveResponse == AteFood){
            std::uniform_int_distribution<int> distrib(1, SIZE - 1); // Define a uniform distribution
            do {
                game.food = Point{distrib(gen), distrib(gen)}; // Generate random coordinates
            } while (game.snake.isSnakePosition(game.food));
        }

        display.displayGame(game, lastMove);

        Sleep(20);
    }
}

Direction GetNextMove(Game& game){
    Point positionDelta = game.food - game.snake.getHeadPosition();

    bool isMakingProgress = (game.snake.heading == Up && positionDelta.x < 0) ||
            (game.snake.heading == Down && positionDelta.x > 0) ||
            (game.snake.heading == Left && positionDelta.y < 0) ||
            (game.snake.heading == Right && positionDelta.y > 0);

    if (isMakingProgress)
        return None;

    if ((game.snake.heading == Down && positionDelta.y == 0 && positionDelta.x < 0) ||
        game.snake.heading == Up && positionDelta.y == 0 && positionDelta.x > 0){

        auto diff = game.snake.getHeadPosition() - game.snake.getAveragePosition();
        return diff.y > 0 ? Right : Left;
    }


    if ((game.snake.heading == Right && positionDelta.x == 0 && positionDelta.y < 0) ||
        game.snake.heading == Left && positionDelta.x == 0 && positionDelta.y > 0){
        // food is above head but heading down.

        auto diff = game.snake.getHeadPosition() - game.snake.getAveragePosition();
        return diff.x > 0 ? Up : Down;
    }

    if (game.snake.heading == Down || game.snake.heading == Up)
        return positionDelta.y > 0 ? Right : Left;

    return positionDelta.x > 0 ? Down : Up;
}


//MoveSet GetNewMoveSet(Game& game){
//
//    auto snake = game.snake.copy();
//
//    Point positionDelta = game.food - game.snake.getHeadPosition();
//    std::vector<Direction> moves{};
//
//
//    if (snake.heading == Up || snake.heading == Down) {
//        // do left-right moves first
//
//        Direction firstMove = positionDelta.y > 0 ? Right : Left;
//        moves.push_back(firstMove);
//        for(int i = 0; i < std::abs(positionDelta.y) - 1; i++){
//            moves.push_back(None);
//        }
//
//        Direction secondMove = positionDelta.x > 0 ? Down : Up;
//        moves.push_back(secondMove);
//        for(int i = 0; i < std::abs(positionDelta.x) - 1; i++){
//            moves.push_back(None);
//        }
//    }
//    else{
//        // do up-down moves first
//
//        Direction secondMove = positionDelta.x > 0 ? Down : Up;
//        moves.push_back(secondMove);
//        for(int i = 0; i < std::abs(positionDelta.x) - 1; i++){
//            moves.push_back(None);
//        }
//
//        Direction firstMove = positionDelta.y > 0 ? Right : Left;
//        moves.push_back(firstMove);
//        for(int i = 0; i < std::abs(positionDelta.y) - 1; i++){
//            moves.push_back(None);
//        }
//    }
//
//    return MoveSet{moves};
//}