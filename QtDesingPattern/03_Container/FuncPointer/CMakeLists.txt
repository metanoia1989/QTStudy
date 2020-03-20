cmake_minimum_required(VERSION 3.5)

project(FuncPointer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui)

add_executable(FuncPointer
  main.cpp
)
target_link_libraries(FuncPointer Qt5::Core Qt5::Gui)
