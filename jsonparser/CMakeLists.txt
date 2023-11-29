cmake_minimum_required(VERSION 3.2...3.5)

project(parser)

find_package(Boost REQUIRED)

set(PARSER_SOURCE
    parser.cpp
    parser.hpp)

add_library(json-parser-lib STATIC ${PARSER_SOURCE})
target_include_directories(json-parser-lib PUBLIC ${Boost_INCLUDE_DIRS})