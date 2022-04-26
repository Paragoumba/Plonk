cmake_minimum_required(VERSION 3.22)
project(Plonk)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Plonk main.cpp ui/MainWindow.cpp ui/MainWindow.hpp ui/MainWindow.ui ui/App.cpp ui/App.hpp ui/App.ui)

target_link_libraries(Plonk
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )