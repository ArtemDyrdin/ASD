cmake_minimum_required(VERSION 3.25)
project(lab_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_2 main.cpp)
file(COPY input.txt DESTINATION "/")