cmake_minimum_required(VERSION 3.4)
project(ini)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c98")

set(SOURCE_FILES main.c)
add_executable(ini ${SOURCE_FILES})