# cmake_minimum_required(VERSION <specify CMake version here>)
project(Prakt2 C)

set(CMAKE_C_STANDARD 90)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -pedantic-errors")

add_executable(Prakt2 main.c)