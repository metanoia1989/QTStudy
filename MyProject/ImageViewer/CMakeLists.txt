cmake_minimum_required(VERSION 3.5)

project(ImageViewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/QtAwesome)

add_executable(ImageViewer
  main.cpp
  mainwindow.cpp
  mainwindow.h
  utils.hpp
)

target_link_libraries(ImageViewer PRIVATE 
  Qt5::Widgets
  QtAwesome)
