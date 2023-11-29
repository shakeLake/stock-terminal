cmake_minimum_required(VERSION 3.2...3.5)

project(api)

add_subdirectory("../../jsonparser" "jsonparser-build")

add_executable(jsonparser_example main.cpp)
target_link_libraries(jsonparser_example PRIVATE json-parser-lib)