cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(whilone_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable( whilone_game 

                src/cell.cpp
                src/controller.cpp 
                src/creature.cpp 
                src/event.cpp
                src/game.cpp 
                src/item.cpp 
                src/main.cpp 
                src/view_terminal.cpp
                )
