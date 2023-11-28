cmake_minimum_required(VERSION 3.2...3.5)

project(ui)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)

set(APP_SOURCE
        app.cpp
        mainwindow.cpp
        "include/mainwindow.hpp"
        toolbar.cpp
        "include/toolbar.hpp"
)

add_library(app-lib STATIC ${APP_SOURCE})

target_link_libraries(app-lib PUBLIC Qt6::Core)
target_link_libraries(app-lib PUBLIC Qt6::Widgets)
target_link_libraries(app-lib PUBLIC Qt6::Gui)

add_executable(Terminal app.cpp)
target_link_libraries(Terminal PRIVATE app-lib)