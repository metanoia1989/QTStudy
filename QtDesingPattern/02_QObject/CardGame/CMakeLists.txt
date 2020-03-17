cmake_minimum_required(VERSION 3.5)

project(CardGame LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(CardGame
    main.cpp
    blackjack.cpp
    blackjack.h
    blackjack.ui
    card.cpp
    card.h
    carddeck.cpp
    carddeck.h
    cardhand.cpp
    cardhand.h
    res.qrc
)

target_link_libraries(CardGame PRIVATE Qt5::Widgets)
