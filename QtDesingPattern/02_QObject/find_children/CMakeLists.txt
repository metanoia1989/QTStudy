cmake_minimum_required(VERSION 3.5)

project(find_children LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(find_children
  main.cpp
  customer.cpp
  customer.h
)
target_link_libraries(find_children Qt5::Core)
