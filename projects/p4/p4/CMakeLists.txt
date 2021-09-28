cmake_minimum_required(VERSION 3.12)
project(p4)

set(CMAKE_CXX_STANDARD 14)

add_executable(p4 blackjack.cpp card.cpp card.h deck.h player.h rand.cpp rand.h deck.cpp hand.cpp player.cpp)