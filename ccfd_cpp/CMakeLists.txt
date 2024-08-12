cmake_minimum_required(VERSION 3.22)
project(CCFD_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(lab1 lab1.cpp)
add_executable(lab2 lab2.cpp)

enable_testing()

add_test(NAME ValgrindTestLab2
         COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 $<TARGET_FILE:lab2>)

set_tests_properties(ValgrindTestLab2 PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR SUMMARY: [^0]+ errors"
)