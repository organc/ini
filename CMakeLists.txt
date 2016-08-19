cmake_minimum_required(VERSION 3.4)
project(ini)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(
        LIBRARY_SOURCE
        src/parser.c
        )

include_directories(src)
add_library(ini STATIC ${LIBRARY_SOURCE})

set(TEST_FILES test/main.c)

add_executable(test_parser ${TEST_FILES})
target_link_libraries(test_parser ini)

ENABLE_TESTING()
add_test(T_INI "${EXECUTABLE_OUTPUT_PATH}/test_parser")
