cmake_minimum_required(VERSION 3.5)

project(Life LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Life
    main.cpp
    lifemainwindow.cpp
    lifemainwindow.h
    lifemainwindow.ui
    lifewidget.cpp
    lifewidget.h
)

target_link_libraries(Life PRIVATE Qt5::Widgets)
