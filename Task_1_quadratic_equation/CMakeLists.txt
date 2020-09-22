cmake_minimum_required(VERSION 3.17)
project(Task_1_quadratic_equation)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Task_1_quadratic_equation quadr_solve.h main.cpp)