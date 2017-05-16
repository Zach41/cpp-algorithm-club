cmake_minimum_required(VERSION 3.7)
project(algorithm_club)

set(CMAKE_CXX_STANDARD 11)
include_directories(src)
set(SOURCE_FILES main.cpp)
add_executable(algorithm_club ${SOURCE_FILES})