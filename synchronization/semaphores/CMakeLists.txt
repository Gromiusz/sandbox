cmake_minimum_required(VERSION 3.20)
project(Semaphores)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(.)
add_executable(ex ex1_s.cpp)