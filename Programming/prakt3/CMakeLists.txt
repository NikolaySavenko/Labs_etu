# cmake_minimum_required(VERSION <specify CMake version here>)
project(Prak3 C)

set(CMAKE_C_STANDARD 90)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -pedantic-errors -Werror=implicit-function-declaration")

add_executable(Prak3 main.c)