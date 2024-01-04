cmake_minimum_required(VERSION 3.2...3.5)

project(ui)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

# error LNK2038: mismatch detected for 
# '_ITERATOR_DEBUG_LEVEL': value '2' doesn't match value '0'

if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Charts)

add_subdirectory("../jsonparser" "jsonparser-build-terminal")

set(APP_SOURCE
        app.cpp
        mainwindow.cpp
        "include/mainwindow.hpp"
        toolbar.cpp
        "include/toolbar.hpp"
        stockslist.cpp
        "include/stockslist.hpp"
        review.cpp
        "include/review.hpp"
        newsfeed.cpp
        "include/newsfeed.hpp"
        stockform.cpp
        "include/stockform.hpp"
        completer.cpp
        "include/completer.hpp"
)

add_library(app-lib STATIC ${APP_SOURCE})

target_link_libraries(app-lib PUBLIC Qt6::Core)
target_link_libraries(app-lib PUBLIC Qt6::Widgets)
target_link_libraries(app-lib PUBLIC Qt6::Gui)
target_link_libraries(app-lib PUBLIC Qt6::Charts)
target_link_libraries(app-lib PUBLIC json-parser-lib)

add_executable(Terminal rmap.qrc app.cpp)
target_link_libraries(Terminal PRIVATE app-lib)