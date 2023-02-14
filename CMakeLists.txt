cmake_minimum_required(VERSION 3.22)
project(SLib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual")
set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC include/SLib/*)
add_library(SLib ${SRC})
set_target_properties(SLib PROPERTIES LINKER_LANGUAGE CXX)
include_directories(include)

add_executable(test_log tests/log_tests.cpp)
add_executable(test_vector tests/vector_test.cpp)
add_executable(test_list tests/test_list.cpp)
add_executable(test_test tests/test_test.cpp)
add_executable(forward_list_test tests/forward_list_test.cpp)

