cmake_minimum_required(VERSION 3.2...3.5)

project(API)

find_package(Threads REQUIRED)

set(Boost_USE_STATIC_LIBS ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON)  # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED)

set(API_SOURCE
    api.cpp
    "include/api.hpp"
    client.cpp
    "include/client.cpp"
    session.cpp
    "include/session.hpp"
)

add_library(apicalllib STATIC ${API_SOURCE})

target_link_libraries(apicalllib PUBLIC Threads::Threads)
target_link_libraries(apicalllib PUBLIC ${Boost_LIBRARIES})
target_include_directories(apicalllib PRIVATE ${Boost_INCLUDE_DIRS})