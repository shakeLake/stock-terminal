cmake_minimum_required(VERSION 3.2...3.5)

project(parser)

set(Boost_USE_STATIC_LIBS ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON)  # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED)

set(PARSER_SOURCE
    parser.cpp
    parser.hpp
    newsclass.hpp
    timeseries.hpp)

add_library(json-parser-lib STATIC ${PARSER_SOURCE})
target_include_directories(json-parser-lib PUBLIC ${Boost_INCLUDE_DIRS})