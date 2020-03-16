cmake_minimum_required(VERSION 3.5)

project(qt_stream LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(qt_stream
  main.cpp
  qt_stream.hpp
  sizeof.hpp
)
target_link_libraries(qt_stream Qt5::Core)
