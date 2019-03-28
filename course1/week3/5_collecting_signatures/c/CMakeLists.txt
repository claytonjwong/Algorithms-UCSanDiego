cmake_minimum_required(VERSION 3.13)
project(5_collecting_signatures C)

include_directories(SYSTEM ./lib)
set(CMAKE_C_STANDARD 99)

add_executable(5_collecting_signatures main.c)