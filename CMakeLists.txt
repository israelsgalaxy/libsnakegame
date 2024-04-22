cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(snakegame)

add_library(${PROJECT_NAME} snakegame.cpp)