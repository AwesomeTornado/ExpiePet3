cmake_minimum_required(VERSION 4.2)
project(ExpiePet3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#find_package(KF6 REQUIRED COMPONENTS Config)
#target_link_libraries(mytarget PRIVATE KF6::ConfigCore)
find_package(Qt6 COMPONENTS
        Core
        Gui
        DBus
        Widgets
        REQUIRED)
find_package(KF6Config)
#find_package(KF6 REQUIRED COMPONENTS Config)

add_executable(ExpiePet3 main.cpp
        mainsprite.cpp
        mainsprite.h
        mainsprite.ui
        IPC.cpp
        IPC.h
        spriteNode.cpp
        spriteNode.h
        twoBoneKinematic.cpp
        twoBoneKinematic.h
        vMath.cpp
        vMath.h)
target_link_libraries(ExpiePet3
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::DBus
        KF6::ConfigCore
)

