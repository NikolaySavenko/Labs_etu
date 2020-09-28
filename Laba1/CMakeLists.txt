# cmake_minimum_required(VERSION <specify CMake version here>)
project(Laba1 C)

set(CMAKE_C_STANDARD 90)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -pedantic-errors")

add_executable(Laba1 main.c)