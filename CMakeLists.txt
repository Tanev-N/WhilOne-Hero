cmake_minimum_required(VERSION 3.27)
project(whilone_game)

set(CMAKE_CXX_STANDARD 17)

add_executable(whilone_game Main/cell.cpp Main/controller.cpp Main/creature.cpp Main/event.cpp
        Main/game.cpp Main/item.cpp Main/main.cpp Main/view_Terminal.cpp)
