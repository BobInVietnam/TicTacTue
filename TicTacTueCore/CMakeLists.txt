cmake_minimum_required(VERSION 3.16)

project(TicTacTueCore LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

qt_add_library(TicTacTueCore STATIC)

qt_add_qml_module(TicTacTueCore
  URI TicTacTueCore
  VERSION 1.0
  SOURCES
  SOURCES
    board.h board.cpp
    player.h player.cpp
    game.h game.cpp
    tictactuecore.h
    tictactuecore.cpp
    SOURCES countdowntimer.h countdowntimer.cpp
    SOURCES gameclient.h gameclient.cpp
    SOURCES offlinegame.h
    SOURCES offlinegame.cpp
    SOURCES onlinegame.h
    SOURCES onlinegame.cpp
    SOURCES aigame.h
    SOURCES aigame.cpp
)

target_link_libraries(TicTacTueCore PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(TicTacTueCore PRIVATE TICTACTUECORE_LIBRARY)
