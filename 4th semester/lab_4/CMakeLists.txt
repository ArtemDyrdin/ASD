cmake_minimum_required(VERSION 3.25)
project(lab_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_4 main.cpp)
file(COPY input.txt DESTINATION "/")
