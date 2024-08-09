cmake_minimum_required(VERSION 3.10)
project(memory)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(block blockmemory.cpp)
add_executable(struct structmemory.cpp)
add_executable(aux auxprocess.cpp)
add_executable(read read.cpp)

target_link_libraries(struct rt)
target_link_libraries(aux rt)
target_link_libraries(read rt)