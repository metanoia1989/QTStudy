cmake_minimum_required(VERSION 3.5)

project(MetaType LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Widgets)

add_executable(MetaType
  main.cpp
  fraction.h
)
target_link_libraries(MetaType Qt5::Widgets)
