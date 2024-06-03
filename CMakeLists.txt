cmake_minimum_required(VERSION 3.28)
project(Snake)

set(CMAKE_CXX_STANDARD 23)

add_executable(Snake  main.cpp
        Game.cpp
        Snake.cpp
        Display.cpp
        Point.cpp
        Game.h
        Snake.h
        Display.h
        Point.h
        Direction.h
        MoveResponse.h
        MoveSet.cpp
        MoveSet.h
        Astar/AstarSearch.cpp
        Astar/AstarSearch.h
        Astar/AStarNode.h
)
