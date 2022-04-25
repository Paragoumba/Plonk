cmake_minimum_required(VERSION 3.22)
project(Plonk)

set(CMAKE_CXX_STANDARD 23)

add_executable(Plonk main.cpp)

target_link_libraries(Plonk SDL2 SDL2_ttf)