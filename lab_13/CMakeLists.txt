cmake_minimum_required(VERSION 3.25)
project(lab_13)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_13 main.cpp)
file(COPY text.txt DESTINATION "/")
