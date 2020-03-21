cmake_minimum_required(VERSION 3.5)

project(MultipleView LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Gui Widgets REQUIRED)

add_executable(MultipleView
    main.cpp
    widget.cpp
    widget.hpp
    createModel.hpp
)

target_link_libraries(MultipleView PRIVATE Qt5::Gui Qt5::Widgets)
