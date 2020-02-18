cmake_minimum_required(VERSION 3.5)

project(Console LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Qt5 COMPONENTS Core Sql REQUIRED)

add_executable(Console
  main.cpp
)

qt5_use_modules(Console Core Sql)

configure_file(sample.csv ${CMAKE_CURRENT_BINARY_DIR}/sample.csv COPYONLY)
