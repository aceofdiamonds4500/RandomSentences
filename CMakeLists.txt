cmake_minimum_required(VERSION 4.0)
project(RandomSentences)

set(CMAKE_CXX_STANDARD 20)

add_executable(RandomSentences src/main.cpp
        src/Rules.h)
