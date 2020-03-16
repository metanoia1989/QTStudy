cmake_minimum_required(VERSION 3.5)

project(EventLoop LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# set(ObjBrowserDir ${CMAKE_CURRENT_SOURCE_DIR}/lib/objectbrowser)
# FILE(GLOB ObjectBrowserSrc
#   ${ObjBrowserDir}/*.cpp 
#   ${ObjBrowserDir}/*.h 
#   ${ObjBrowserDir}/*.qrc
#   ${ObjBrowserDir}/*.ui)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/objectbrowser)

add_executable(EventLoop
  main.cpp
  keysequencelabel.cpp
  keysequencelabel.h
  keysequencelabel.ui
)

target_link_libraries(EventLoop PRIVATE Qt5::Widgets)
target_link_libraries(EventLoop PRIVATE objectbrowser)
