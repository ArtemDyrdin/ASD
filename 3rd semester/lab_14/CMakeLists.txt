cmake_minimum_required(VERSION 3.25)
project(lab_14)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_14 main.cpp)
file(COPY "input.txt" DESTINATION "/")