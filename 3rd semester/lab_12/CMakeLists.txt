cmake_minimum_required(VERSION 3.25)
project(lab_12)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_12 main.cpp ExternalMultiphaseMergeSort.h)
file(COPY input.txt DESTINATION "/")
