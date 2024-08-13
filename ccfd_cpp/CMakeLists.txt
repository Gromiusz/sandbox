cmake_minimum_required(VERSION 3.22)
project(CCFD_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest CONFIG REQUIRED)

# set(SRC )
# set(LIBSRC )
# set(UTSRC)

add_library(lab2-lib STATIC lab2.cpp)

add_executable(lab1 lab1.cpp)
add_executable(lab2-main lab2-main.cpp)

add_executable(lab2-ut lab2-ut.cpp)

target_link_libraries(lab2-ut PUBLIC GTest::gtest)
target_link_libraries(lab2-ut PUBLIC lab2-lib)
target_link_libraries(lab2-main PUBLIC lab2-lib)

enable_testing()

add_test(NAME ValgrindTestLab2
         COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 $<TARGET_FILE:lab2-main>)

set_tests_properties(ValgrindTestLab2 PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR SUMMARY: [^0]+ errors"
)

add_test(NAME ValgrindTestLab2UT
         COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 $<TARGET_FILE:lab2-ut>)

set_tests_properties(ValgrindTestLab2UT PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR SUMMARY: [^0]+ errors"
)

include(GoogleTest)
gtest_discover_tests(lab2-ut)