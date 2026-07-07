cmake_minimum_required(VERSION 4.2)
project(ExpiePet3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        DBus
        Widgets
        REQUIRED)

add_executable(ExpiePet3 main.cpp
        mainsprite.cpp
        mainsprite.h
        mainsprite.ui
        IPC.cpp
        IPC.h)
target_link_libraries(ExpiePet3
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::DBus
)

