cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(6nimmt)

include_directories( ./src )

add_executable( mussolini ./src/main.cpp ./src/Card.cpp ./src/Board.cpp ./src/Player.cpp )