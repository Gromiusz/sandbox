cmake_minimum_required(VERSION 3.22)
project(CCFD_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest CONFIG REQUIRED)

# set(SRC lab3/lab3-main.cpp)
# set(LIBSRC lab3/lab3-lib.cpp)
# set(UTSRC lab3/lab3-ut.cpp)

set(SRC lab4/lab4-main.cpp)
set(LIBSRC lab4/lab4-lib.cpp)
set(UTSRC lab4/lab4-ut.cpp)

add_library(lab-lib STATIC ${LIBSRC})

add_executable(lab-main ${SRC})
add_executable(lab-ut ${UTSRC})

target_link_libraries(lab-ut PUBLIC GTest::gtest)
target_link_libraries(lab-ut PUBLIC lab-lib)
target_link_libraries(lab-main PUBLIC lab-lib)

enable_testing()

add_test(NAME ValgrindTestlab
         COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 $<TARGET_FILE:lab-main>)

set_tests_properties(ValgrindTestlab PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR SUMMARY: [^0]+ errors"
)

add_test(NAME ValgrindTestlabUT
         COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 $<TARGET_FILE:lab-ut>)

set_tests_properties(ValgrindTestlabUT PROPERTIES
    FAIL_REGULAR_EXPRESSION "ERROR SUMMARY: [^0]+ errors"
)

include(GoogleTest)
gtest_discover_tests(lab-ut)