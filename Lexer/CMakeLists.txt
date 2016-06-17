cmake_minimum_required(VERSION 3.5)
project(Lexer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES LexicalAnalyser.cpp LexicalAnalyser.h main.cpp)
add_executable(Lexer ${SOURCE_FILES})