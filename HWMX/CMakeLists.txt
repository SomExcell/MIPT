cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

project(HWMX)

include_directories("header/")

set(SOURCES source/main.cpp)

set(HEADERS header/matrix.hpp)

set(TESTS Tests.txt)

add_executable(HWMX ${SOURCES} ${HEADERS} ${TESTS})