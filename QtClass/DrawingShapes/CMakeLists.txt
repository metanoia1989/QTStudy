cmake_minimum_required(VERSION 3.5)

project(DrawingShapes LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS REQUIRED
    Core Gui Widgets)

add_executable(DrawingShapes
  main.cpp
  customwidget.cpp
)
target_link_libraries(DrawingShapes
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets)
