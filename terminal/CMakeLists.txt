cmake_minimum_required(VERSION 3.2...3.5)

project(ui)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Quick Qml Charts)

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
target_link_libraries(app-lib PUBLIC Qt6::Quick)
target_link_libraries(app-lib PUBLIC Qt6::Qml)
target_link_libraries(app-lib PUBLIC Qt6::Charts)

add_executable(Terminal rmap.qrc app.cpp)
target_link_libraries(Terminal PRIVATE app-lib)