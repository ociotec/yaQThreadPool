cmake_minimum_required(VERSION 2.8)

project(yatp)

set(CMAKE_INCLUDE_CURRECT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(src)
add_subdirectory(tests)
