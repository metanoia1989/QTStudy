cmake_minimum_required(VERSION 3.5)

set(HEADER_FILES
    QtAwesome.h
    QtAwesomeAnim.h)

set(SOURCE_FILES
    QtAwesome.cpp
    QtAwesomeAnim.cpp)

qt5_add_resources(RESOURCE_FILES
    QtAwesome.qrc)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 REQUIRED Core Gui Widgets)

add_library(QtAwesome STATIC 
    ${HEADER_FILES} 
    ${SOURCE_FILES}
    ${RESOURCE_FILES})

target_link_libraries(QtAwesome
    Qt5::Core 
    Qt5::Gui
    Qt5::Widgets)

target_include_directories(QtAwesome  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})
