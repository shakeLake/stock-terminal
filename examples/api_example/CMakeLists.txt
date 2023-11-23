cmake_minimum_required(VERSION 3.2...3.5)

project(api)

add_subdirectory("../../api" "api-build")

add_executable(api_example main.cpp)
target_link_libraries(api_example PRIVATE apicalllib)