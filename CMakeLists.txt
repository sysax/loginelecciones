cmake_minimum_required(VERSION 3.16)
project(LoginElecciones VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

add_executable(LoginElecciones
    main.cpp
    loginwindow.h
    loginwindow.cpp
)

target_link_libraries(LoginElecciones PRIVATE Qt6::Widgets Qt6::Sql)

