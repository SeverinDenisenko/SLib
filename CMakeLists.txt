cmake_minimum_required(VERSION 3.22)
project(SLib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual")
set(CMAKE_CXX_STANDARD 20)

add_library(SLib include/SLib/SLib.h src/SLog.cpp include/SLib/SLog.h include/SLib/SVector.h include/SLib/SException.h)

include_directories(include)

add_executable(test_log tests/log_tests.cpp)
target_link_libraries(test_log SLib)

add_executable(test_vector tests/vector_test.cpp)
target_link_libraries(test_vector SLib)

