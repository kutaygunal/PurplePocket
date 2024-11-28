cmake_minimum_required(VERSION 3.16)
project(QtProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_executable(QtProject
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(QtProject PRIVATE
    Qt6::Core
    Qt6::Widgets
)
