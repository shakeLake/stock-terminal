cmake_minimum_required(VERSION 3.2...3.5)

project(StockTerminal)

set(CMAKE_BUILD_TYPE Release)

# error LNK2038: mismatch detected for 
# '_ITERATOR_DEBUG_LEVEL': value '2' doesn't match value '0'
if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
endif()

# add_subdirectory("examples" "examples-build")

add_subdirectory("terminal" "terminal-build")