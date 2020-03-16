cmake_minimum_required(VERSION 3.5)

project(person_bunch LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(person_bunch
  main.cpp
  person.cpp
  person.h
)
target_link_libraries(person_bunch Qt5::Core)
