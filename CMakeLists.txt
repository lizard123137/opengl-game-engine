# /CMakeLists.txt

cmake_minimum_required(VERSION 3.20.0)
project(opengl-game-engine VERSION 0.0.1)

cmake_policy(SET CMP0072 NEW)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Core)
add_subdirectory(Examples)

add_compile_options(-Wall)
