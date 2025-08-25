cmake_minimum_required(VERSION 3.22.2)
project(lazysql)

set(CMAKE_C_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(deps/notcurses)

add_subdirectory(src)

