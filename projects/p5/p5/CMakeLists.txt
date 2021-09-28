cmake_minimum_required(VERSION 3.12)
project(p5)

set(CMAKE_CXX_STANDARD 14)

add_executable(p5 dlist.h  dlist_impl.h call.cpp)